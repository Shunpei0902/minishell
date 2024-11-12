/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:23:30 by sasano            #+#    #+#             */
/*   Updated: 2024/11/12 19:18:43 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char check_isalpha_isunder(char str) 
{
    if (ft_isalpha(str) || str == '_')
        return (str);
    return (0);
}

static char *get_env(char *line, int *i)
{
    int start;

    if (line[*i] != '$')
        return (NULL);
    (*i)++;
    start = *i;
    while (check_isalpha_isunder(line[*i]))
        (*i)++;
    return (getenv(ft_substr(line, start, *i - start)));
}

// パラメータ展開を行う関数
static char *param_expand(char *line, int *i)
{
    int start;
    char *value;
    char *tmp;

    if (line[*i] == '\0')
        return (NULL);
    start = *i;
    // $があった場合の処理
    value = get_env(line, i);
    // それ以外の処理
    if (!value)
    {
        while (line[(*i)] && line[*i] != '$')
        {
            if (line[*i] == '\'')
            {
                while (line[++(*i)] != '\'')
                    ;
            }
            (*i)++;
        }
        value = ft_substr(line, start, *i - start);
    }
    tmp = ft_strjoin(value, param_expand(line, i));
    if (line[start] != '$')
        free(value);
    return (tmp);
}

static char	validate_quote_expand(char *line, int *i, int *start, int *end)
{
	char	quote_flag;

	quote_flag = 0;
	if (check_quote(line, *i))
	{
		quote_flag = line[*i];
		(*i)++;
		*start = *i;
	}
	while (quote_flag)
	{
		// if (line[*i] == '\0' || line[*i] == '\n')
		// {
		// 	tokenize_error(&(line[*start]), line);
		// 	break ;
		// }
		if (line[*i] == quote_flag)
		{
			*end = *i;
			(*i)++;
			return (quote_flag);
		}
		(*i)++;
	}
	return (quote_flag);
}

// クォートを展開する関数
char *quote_expand(char *line, int *i)
{
	int		start;
	int		end;
	char	quote_flag;
	char	*value;
	char	*tmp;

	start = *i;
	// クォーテーションがあったらここで処理
	quote_flag = validate_quote_expand(line, i, &start, &end);
	// なかった場合の処理
	if (!quote_flag)
	{
		while (line[*i] && !check_quote(line, *i))
			end = ++(*i);
	}
	value = ft_substr(line, start, end - start);
	if (line[*i])
	{
		tmp = ft_strjoin(value, quote_expand(line, i));
		free(value);
		value = tmp;
	}
	return (value);
}

// トークンを分割
static void word_split(t_token *tokens)
{
    int i;
    char *line;
    t_token *new_token;
    t_token *tmp;

    i = 0;
    line = tokens->value;
    tokens->value = get_word(line, &i);
    while (line[i])
    {
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (!line[i])
			break ;
        new_token = ft_calloc(1, sizeof(t_token));
        new_token->type = TOKEN_WORD;
        new_token->value = get_word(line, &i);
        tmp = tokens->next;
        tokens->next = new_token;
        new_token->next = tmp;
        tokens = new_token;
    }
    free(line);
}

void expand(t_token *tokens)
{
    int i;
    char *tmp;
    
    while (tokens && g_syntax_error == false)
    {
        if (tokens->type == TOKEN_WORD) {
            i = 0;
            tmp = tokens->value;
            tokens->value = param_expand(tokens->value, &i);
            word_split(tokens);
            i = 0;
            tokens->value = quote_expand(tokens->value, &i);
            free(tmp);
        }
        tokens = tokens->next;
    }
}
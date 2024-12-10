/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:23:30 by sasano            #+#    #+#             */
/*   Updated: 2024/12/10 12:25:47 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_isalpha_isunder(char str)
{
	if (ft_isalpha(str) || ft_isdigit(str) || str == '_')
		return (str);
	return (0);
}

static char	*get_env(char *line, int *i, int *start)
{
	*start = *i;
	if (line[*start] != '$')
		return (NULL);
	if (check_isalpha_isunder(line[*i + 1]) == 0 && line[*i + 1] != '?')
	{
		(*i)++;
		return (ft_substr(line, *start, 1));
	}
	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_last_status));
	}
	while (check_isalpha_isunder(line[*i]))
		(*i)++;
	return (getenv(ft_substr(line, *start + 1, *i - *start - 1)));
}

// パラメータ展開を行う関数
char	*param_expand(char *line, int *i)
{
	int		start;
	char	*value;
	char	*tmp;

	if (!line || line[*i] == '\0')
		return (NULL);
	value = get_env(line, i, &start);
	if (!value && line[start] != '$')
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
char	*quote_expand(char *line, int *i)
{
	int		start;
	int		end;
	char	quote_flag;
	char	*value;
	char	*tmp;

	if (!line || line[*i] == '\0')
		return (NULL);
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
static void	word_split(t_token *tokens)
{
	int		i;
	char	*line;
	t_token	*new_token;
	t_token	*tmp;

	i = 0;
	line = tokens->value;
	tokens->value = get_word(line, &i);
	if (!line)
		return ;
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

void	expand(t_token *tokens)
{
	int		i;
	char	*tmp;
	t_token	*tmp_token;

	tmp_token = 0;
	while (tokens && g_syntax_error == false)
	{
		if (tokens->type == TOKEN_WORD && (!tmp_token
				|| tmp_token->type != TOKEN_REDIR_HEREDOC))
		{
			i = 0;
			tmp = tokens->value;
			tokens->value = param_expand(tokens->value, &i);
			word_split(tokens);
			i = 0;
			tokens->value = quote_expand(tokens->value, &i);
			free(tmp);
		}
		tmp_token = tokens;
		tokens = tokens->next;
	}
}

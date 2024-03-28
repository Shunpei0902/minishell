/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:35:05 by sasano            #+#    #+#             */
/*   Updated: 2024/03/28 12:37:56 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// トークンの種類を判別する
enum e_token_type	check_token_type(char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (TOKEN_PIPE);
	}
	else if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
		{
			(*i)++;
			return (TOKEN_REDIR_APPEND);
		}
		return (TOKEN_REDIR_IN);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			(*i)++;
			return (TOKEN_REDIR_APPEND);
		}
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

// クォーテーションのチェック
void	check_quotation(char *line, int *i, int *start, int *end)
{
	char	quote;

	if (line[*i] == '\"' || line[*i] == '\'')
	{
		quote = line[*i];
		(*start)++;
		(*i)++;
		while (line[*i] && line[*i] != quote)
		{
			if (line[*i] == '\0' || line[*i] == '\n')
				fatal_error("error: syntax error\n");
			(*i)++;
		}
		*end = *i;
		return ;
	}
	*end = *i + 1;
}

// トークンを追加する
t_token	*add_token(t_token **head, t_token *current, enum e_token_type type,
		char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token) * 1);
	if (!new)
		fatal_error("malloc");
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!*head)
		*head = new;
	if (current)
		current->next = new;
	return (new);
}

// トークンを取得する
t_token	*get_token(t_token **head, t_token *current, char *line, int *i)
{
	int					start;
	int					end;
	char				*value;
	enum e_token_type	type;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		check_quotation(line, i, &start, &end);
		(*i)++;
	}
	type = check_token_type(line, i);
	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND)
		end = *i;
	value = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (!value)
		fatal_error("malloc");
	ft_strlcpy(value, line + start, end - start + 1);
	return (add_token(head, current, type, value));
}

//　トークナイズする
t_token	*tokenize(char *line)
{
	t_token	*head;
	t_token	*current;
	int		i;

	current = NULL;
	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		current = get_token(&head, current, line, &i);
	}
	add_token(&head, current, TOKEN_EOF, NULL);
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:52:14 by sasano            #+#    #+#             */
/*   Updated: 2024/11/12 19:20:52 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quote(char *line, int i)
{
	return (line[i] == '\"' || line[i] == '\'');
}

bool	check_symbol(char *line, int i)
{
	return (!line[i] || line[i] == '\n' || line[i] == ' ' || line[i] == '\t'
		|| line[i] == '\n' || line[i] == '|' || line[i] == '<' || line[i] == '>'
		|| line[i] == ' ' || line[i] == '\t' || line[i] == '\n');
}

enum e_token_type	check_token_type(char *line, int i)
{
	if (line[i] == '|')
		return (TOKEN_PIPE);
	else if (line[i] == '<')
	{
		i++;
		if (line[i] == '<')
			return (TOKEN_REDIR_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (line[i] == '>')
	{
		i++;
		if (line[i] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

// クォーテーションを取り除く処理はexpand.cに移動
static char	validate_quote(char *line, int *i, int *start, int *end)
{
	char	quote_flag;

	quote_flag = 0;
	if (check_quote(line, *i))
	{
		quote_flag = line[*i];
		(*i)++;
		// *start = *i;
	}
	while (quote_flag && g_syntax_error == false)
	{
		if (line[*i] == '\0' || line[*i] == '\n')
		{
			tokenize_error(&(line[*start]), &line);
			(*i)++;
			return (quote_flag);
		}
		if (line[*i] == quote_flag)
		{
			*end = ++(*i);
			// (*i)++;
			return (quote_flag);
		}
		(*i)++;
	}
	return (quote_flag);
}
void	add_token(t_token **head, t_token *current)
{
	t_token	*tmp;

	if (!*head)
		*head = current;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
	}
}

void	add_eof_token(t_token **head)
{
	t_token	*current;

	current = ft_calloc(1, sizeof(t_token));
	current->type = TOKEN_EOF;
	add_token(head, current);
}


char	*get_word(char *line, int *i)
{
	int		start;
	int		end;
	char	quote_flag;
	char	*value;
	char	*tmp;

	start = *i;
	// クォーテーションがあったらここで処理
	quote_flag = validate_quote(line, i, &start, &end);
	// なかった場合の処理
	if (!quote_flag)
	{
		while (!check_symbol(line, *i) && !check_quote(line, *i))
			end = ++(*i);
	}
	value = ft_substr(line, start, end - start);
	if (!check_symbol(line, *i))
	{
		tmp = ft_strjoin(value, get_word(line, i));
		free(value);
		value = tmp;
	}
	return (value);
}

static char	*get_symbol(char *line, int *i, t_token_type type)
{
	char	*value;

	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
	{
		value = ft_calloc(2, sizeof(char));
		value[0] = line[(*i)++];
		return (value);
	}
	value = ft_calloc(3, sizeof(char));
	value[0] = line[(*i)++];
	value[1] = line[(*i)++];
	return (value);
}

static t_token	*get_token(char *line, int *i)
{
	char				*value;
	enum e_token_type	type;
	t_token				*new_token;

	type = check_token_type(line, *i);
	if (type == TOKEN_WORD)
		value = get_word(line, i);
	else
		value = get_symbol(line, i, type);
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->type = type;
	new_token->value = value;
	return (new_token);
}

t_token	*tokenize(char *line)
{
	t_token	*head;
	t_token	*current;
	int		i;

	current = NULL;
	head = NULL;
	g_syntax_error = false;
	i = 0;
	while (line[i] && g_syntax_error == false)
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (!line[i])
			break ;
		current = get_token(line, &i);
		add_token(&head, current);
	}
	add_eof_token(&head);
	return (head);
}

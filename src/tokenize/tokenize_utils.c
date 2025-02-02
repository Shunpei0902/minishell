/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:30:25 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 10:10:05 by sasano           ###   ########.fr       */
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
		|| line[i] == '\n' || line[i] == '|' || line[i] == '<'
		|| line[i] == '>' || line[i] == ' ' || line[i] == '\t'
		|| line[i] == '\n');
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

char	validate_quote(char *line, int *i, int *start, int *end)
{
	char	quote_flag;

	quote_flag = 0;
	if (check_quote(line, *i))
	{
		quote_flag = line[*i];
		(*i)++;
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

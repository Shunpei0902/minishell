/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:52:14 by sasano            #+#    #+#             */
/*   Updated: 2024/12/13 12:11:59 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!line)
		return (NULL);
	start = *i;
	quote_flag = validate_quote(line, i, &start, &end);
	if (g_syntax_error == true)
		return (NULL);
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
	while (g_syntax_error == false && line[i])
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

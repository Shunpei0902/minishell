/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_rem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:30:23 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 10:07:03 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	quote_flag = validate_quote_expand(line, i, &start, &end);
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

static void	expand_quote_rem_tok(t_token *tokens)
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
			tokens->value = quote_expand(tokens->value, &i);
			free(tmp);
		}
		tmp_token = tokens;
		tokens = tokens->next;
	}
}

void	expand_quote_removal(t_node *node)
{
	if (!node || node->type == NODE_REDIR_HEREDOC)
		return ;
	expand_quote_rem_tok(node->args);
	expand_quote_rem_tok(node->filename);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->next);
}

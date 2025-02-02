/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:31:23 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 09:57:32 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split(char *line, int i, t_token *tokens)
{
	t_token	*new_token;
	t_token	*tmp;

	while (line && line[i])
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
}

static void	word_split(t_token *tokens)
{
	int		i;
	char	*line;

	if (!tokens)
		return ;
	i = 0;
	line = tokens->value;
	tokens->value = get_word(line, &i);
	if (!line)
		return ;
	split(line, i, tokens);
	free(line);
}

static void	word_split_tok(t_token *tokens)
{
	while (tokens)
	{
		word_split(tokens);
		tokens = tokens->next;
	}
}

void	expand_word_splitting(t_node *node)
{
	if (!node || node->type == NODE_REDIR_HEREDOC)
		return ;
	word_split_tok(node->args);
	word_split_tok(node->filename);
	expand_word_splitting(node->redirects);
	expand_word_splitting(node->next);
}

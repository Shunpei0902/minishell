/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:34:54 by sasano            #+#    #+#             */
/*   Updated: 2024/03/31 08:47:24 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	// node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		fatal_error("malloc");
	node->type = type;
	node->next = NULL;
	return (node);
}

t_token	*tokdup(t_token *token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		fatal_error("malloc");
	new_token->type = token->type;
	new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL)
		fatal_error("ft_strdup");
	new_token->next = NULL;
	return (new_token);
}

void	append_tokens(t_token **tokens, t_token *token)
{
	if (*tokens == NULL)
	{
		*tokens = token;
		return ;
	}
	return (append_tokens(&(*tokens)->next, token));
}

t_node	*parse(t_token *tokens)
{
	t_node *node;

	node = new_node(NODE_COMMAND);
	while (tokens != NULL && tokens->type != TOKEN_EOF)
	{
		if (tokens->type == TOKEN_WORD)
			append_tokens(&node->args, tokdup(tokens));
		else
			fatal_error("parse error");
		tokens = tokens->next;
	}
	return (node);
}
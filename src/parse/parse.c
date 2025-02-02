/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:34:54 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 15:32:58 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = xcalloc(1, sizeof(t_node));
	node->type = type;
	if (type == NODE_COMMAND)
	{
		node->inpipe[0] = STDIN_FILENO;
		node->inpipe[1] = -1;
		node->outpipe[0] = -1;
		node->outpipe[1] = STDOUT_FILENO;
	}
	return (node);
}

t_token	*tokdup(t_token *token)
{
	t_token	*new_token;

	new_token = xcalloc(1, sizeof(t_token));
	new_token->type = token->type;
	new_token->value = xstrdup(token->value);
	if (new_token->value == NULL)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

void	append_tokens(t_token **tokens, t_token *token)
{
	if (token == NULL)
		return ;
	if (*tokens == NULL)
	{
		*tokens = token;
		return ;
	}
	return (append_tokens(&(*tokens)->next, token));
}

void	append_redirects(t_node **redirects, t_token *token, t_token *filename)
{
	t_node		*node;
	t_node		*tmp;
	t_node_type	type;

	type = check_redirect(token);
	node = new_node(type);
	node->filename = filename;
	if (type == NODE_REDIR_IN || type == NODE_REDIR_HEREDOC)
		node->targetfd = STDIN_FILENO;
	else if (type == NODE_REDIR_OUT || type == NODE_REDIR_APPEND)
		node->targetfd = STDOUT_FILENO;
	if (*redirects == NULL)
	{
		*redirects = node;
		return ;
	}
	tmp = *redirects;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			break ;
	}
	tmp->next = node;
}

t_node	*parse(t_token *tokens)
{
	t_node	*node;

	node = new_node(NODE_COMMAND);
	while (tokens != NULL && tokens->type != TOKEN_EOF)
	{
		if (tokens->type == TOKEN_WORD)
			append_tokens(&node->args, tokdup(tokens));
		else if (check_redirect(tokens))
		{
			append_redirects(&node->redirects, tokens, tokdup(tokens->next));
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_PIPE && !check_pipe(tokens->next))
		{
			node->next = parse(tokens->next);
			break ;
		}
		else
			parse_error(tokens->value, &tokens);
		tokens = tokens->next;
	}
	return (node);
}

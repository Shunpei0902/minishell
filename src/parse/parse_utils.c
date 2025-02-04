/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:09:12 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 14:40:34 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	check_redirect(t_token *token)
{
	if (!token || !token->next || !token->next->value)
		return (0);
	if (token->next->type != TOKEN_EOF && token->next->type != TOKEN_WORD)
		return (0);
	if (token->type == TOKEN_REDIR_IN)
		return (NODE_REDIR_IN);
	else if (token->type == TOKEN_REDIR_OUT)
		return (NODE_REDIR_OUT);
	else if (token->type == TOKEN_REDIR_APPEND)
		return (NODE_REDIR_APPEND);
	else if (token->type == TOKEN_REDIR_HEREDOC)
		return (NODE_REDIR_HEREDOC);
	return (0);
}

bool	check_pipe(t_token *token)
{
	if (token == NULL)
		return (true);
	if (token->type != TOKEN_WORD)
		return (true);
	return (false);
}

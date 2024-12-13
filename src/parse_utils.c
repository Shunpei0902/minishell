/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:09:12 by sasano            #+#    #+#             */
/*   Updated: 2024/12/12 23:11:14 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_type	check_redirect(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		return (NODE_REDIR_IN);
	else if (token->type == TOKEN_REDIR_OUT)
		return (NODE_REDIR_OUT);
	else if (token->type == TOKEN_REDIR_APPEND)
		return (NODE_REDIR_APPEND);
	else if (token->type == TOKEN_REDIR_HEREDOC)
		return (NODE_REDIR_HEREDOC);
	return (NODE_COMMAND);
}

bool	check_pipe(t_token *token)
{
	if (token == NULL)
		return (true);
	if (token->type != TOKEN_WORD)
		return (true);
	return (false);
}

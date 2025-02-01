/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:36:41 by sasano            #+#    #+#             */
/*   Updated: 2025/02/01 19:32:46 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_pipe(int *srcpipe, int *destpipe)
{
	destpipe[0] = srcpipe[0];
	destpipe[1] = srcpipe[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe");
	cpy_pipe(node->outpipe, node->next->inpipe);
}

void	pipe_child(t_node *node)
{
	xclose(node->outpipe[0]);
	xdup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		xclose(node->inpipe[0]);
	xdup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		xclose(node->outpipe[1]);
}

void	pipe_parent(t_node *node)
{
	if (node->next)
		xclose(node->outpipe[1]);
	if (node->inpipe[0] != STDIN_FILENO)
		xclose(node->inpipe[0]);
}

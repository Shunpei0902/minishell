/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:36:41 by sasano            #+#    #+#             */
/*   Updated: 2024/04/07 17:05:51 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void cpy_pipe(int *srcpipe, int*destpipe)
{
    destpipe[0] = srcpipe[0];
    destpipe[1] = srcpipe[1];
}

void prepare_pipe(t_node *node)
{
    if (node->next == NULL)
        return ;
    if (pipe(node->outpipe) < 0)
        fatal_error("pipe");
    cpy_pipe(node->outpipe, node->next->inpipe);
}


void pipe_child(t_node *node)
{
    close(node->outpipe[0]);
    close(node->inpipe[1]);
    dup2(node->inpipe[0], STDIN_FILENO);
    if (node->inpipe[0] != STDIN_FILENO)
        close(node->inpipe[0]);
    dup2(node->outpipe[1], STDOUT_FILENO);
    if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void pipe_parent(t_node *node)
{
    if (node->next)
        close(node->outpipe[1]);
    if (node->inpipe[0] != STDIN_FILENO)
        close(node->inpipe[0]);
}


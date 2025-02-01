/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:59:37 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 01:21:19 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_readline_interrupted = false;

int	stash_fd(int fd)
{
	int			stashed_fd;
	struct stat	statbuf;

	stashed_fd = 10;
	while (!fstat(stashed_fd, &statbuf))
		stashed_fd++;
	xdup2(fd, stashed_fd);
	xclose(fd);
	return (stashed_fd);
}

void	open_redir_file(t_node *node)
{
	if (!node || !node->filename || !node->filename->value)
		return ;
	if (node->type == NODE_REDIR_IN && node->filename && node->filename->value)
		node->filefd = open(node->filename->value, O_RDONLY);
	else if (node->type == NODE_REDIR_OUT && node->filename
		&& node->filename->value)
		node->filefd = open(node->filename->value, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (node->type == NODE_REDIR_APPEND)
		node->filefd = open(node->filename->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == NODE_REDIR_HEREDOC)
		node->filefd = read_heredoc(node->filename->value);
	if (node->filefd < 0)
		err_exit(node->filename->value, "open", 1);
	node->filefd = stash_fd(node->filefd);
	open_redir_file(node->next);
}

void	redirect(t_node *node)
{
	if (!node)
		return ;
	node->stashed_targetfd = stash_fd(node->targetfd);
	xdup2(node->filefd, node->targetfd);
	redirect(node->next);
}

void	reset_redirect(t_node *node)
{
	if (!node)
		return ;
	reset_redirect(node->next);
	xclose(node->filefd);
	xclose(node->targetfd);
	xdup2(node->stashed_targetfd, node->targetfd);
	xclose(node->stashed_targetfd);
}

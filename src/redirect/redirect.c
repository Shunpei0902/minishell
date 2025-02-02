/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:59:37 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 16:40:08 by sasano           ###   ########.fr       */
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

static int error_case_redirect(t_node *node)
{
	if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT)
	{
		error_message3(node->filename->value, ": ",
			"No such file or directory");
		// g_last_status = 1;
		return (1);
	}
	else if (node->type == NODE_REDIR_APPEND || node->type == NODE_REDIR_HEREDOC)
	{
		g_last_status = 130;
		return (130);
	}
	return (0);
}

int	open_redir_file(t_node *node)
{
	if (!node || !node->filename || !node->filename->value)
		return (0);
	if (node->type == NODE_REDIR_IN && node->filename && node->filename->value)
		node->filefd = open(node->filename->value, O_RDONLY);
	else if (node->type == NODE_REDIR_OUT && node->filename
		&& node->filename->value)
		node->filefd = open(node->filename->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_REDIR_APPEND)
		node->filefd = open(node->filename->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == NODE_REDIR_HEREDOC)
		node->filefd = read_heredoc(&(node->filename->value));
	if (node->filefd < 0)
		return (error_case_redirect(node));
	node->filefd = stash_fd(node->filefd);
	open_redir_file(node->next);
	return (0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:59:37 by sasano            #+#    #+#             */
/*   Updated: 2025/01/17 21:22:43 by sasano           ###   ########.fr       */
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
	if (dup2(fd, stashed_fd) == -1)
		fatal_error("dup2");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashed_fd);
}

void	open_redir_file(t_node *node)
{
	if (!node)
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
	if (dup2(node->filefd, node->targetfd) == -1)
		fatal_error("dup2");
	redirect(node->next);
}

void	reset_redirect(t_node *node)
{
	if (!node)
		return ;
	reset_redirect(node->next);
	close(node->filefd);
	close(node->targetfd);
	if (dup2(node->stashed_targetfd, node->targetfd) == -1)
		fatal_error("dup2");
	close(node->stashed_targetfd);
}

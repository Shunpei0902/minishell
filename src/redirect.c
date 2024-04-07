/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:59:37 by sasano            #+#    #+#             */
/*   Updated: 2024/04/06 15:53:47 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0 && *line != '\0')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

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
	if (node->type == NODE_REDIR_IN)
		node->filefd = open(node->filename->value, O_RDONLY);
	else if (node->type == NODE_REDIR_OUT)
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
	printf("node->filename: %s\n", node->filename->value);
	printf("node->filefd: %d\n", node->filefd);
	redirect(node->next);
}

void	reset_redirect(t_node *node)
{
	if (!node)
		return ;
	close(node->filefd);
	close(node->targetfd);
	if (dup2(node->stashed_targetfd, node->targetfd) == -1)
		fatal_error("dup2");
	close(node->stashed_targetfd);
	reset_redirect(node->next);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:07:54 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 20:02:39 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external_command(t_node *node)
{
	const char	*path;
	char		**argv;

	argv = tokens_to_argv(node->args);
	path = argv[0];
	if (path && ft_strchr(path, '/') == NULL)
		path = search_path(argv[0]);
	validate_path(path, argv[0]);
	execve(path, argv, get_environ());
	free_argv(argv);
	reset_redirect(node->redirects);
	fatal_error("execve");
}

void	exec_pipe_child(t_node *node)
{
	reset_signal();
	pipe_child(node);
	redirect(node->redirects);
	if (is_builtin(node))
		exit(exec_builtin(node));
	else
		exec_external_command(node);
}

pid_t	exec_pipe_parent(t_node *node, pid_t pid)
{
	set_signal_parent();
	pipe_parent(node);
	if (node->next)
		return (exec_pipe(node->next));
	return (pid);
}

pid_t	exec_pipe(t_node *node)
{
	pid_t	pid;

	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		exec_pipe_child(node);
	else
		pid = exec_pipe_parent(node, pid);
	return (pid);
}

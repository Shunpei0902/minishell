/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:07:54 by sasano            #+#    #+#             */
/*   Updated: 2024/12/13 18:37:37 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_command(int builtin_id, char **argv, t_node *node)
{
	exec_builtin(builtin_id, argv);
	reset_redirect(node->redirects);
	// fatal_error("builtin");
}

void	exec_external_command(const char *path, char **argv, t_node *node)
{
	extern char	**environ;

	if (path && path[0] != '/' && path[0] != '.')
		path = search_path(argv[0]);
	validate_path(path, argv[0]);
	execve(path, argv, environ);
	reset_redirect(node->redirects);
	fatal_error("execve");
}

void	exec_pipe_child(t_node *node)
{
	extern char	**environ;
	const char	*path;
	char		**argv;
	int			builtin_id;

	reset_signal();
	pipe_child(node);
	redirect(node->redirects);
	argv = tokens_to_argv(node->args);
	if (argv == NULL)
		exit(1);
	path = argv[0];
	builtin_id = is_builtin(argv[0]);
	if (builtin_id > 0)
		exec_builtin_command(builtin_id, argv, node);
	else
		exec_external_command(path, argv, node);
}

void	exec_pipe_parent(t_node *node, pid_t pid)
{
	pipe_parent(node);
	if (node->next)
		exec_pipe(node->next);
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
		exec_pipe_parent(node, pid);
	return (pid);
}

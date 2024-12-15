/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:31:38 by sasano            #+#    #+#             */
/*   Updated: 2024/12/13 18:37:31 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashmap.h"
#include <sys/wait.h>

int		g_last_status;

int	wait_pipe(pid_t last_pid)
{
	pid_t	wait_pid;
	int		wstatus;
	int		status;

	status = 0;
	while (1)
	{
		wait_pid = wait(&wstatus);
		if (wait_pid == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			fatal_error("wait");
		}
	}
	return (status);
}

// pid_t	exec_pipe(t_node *node)
// {
// 	extern char	**environ;
// 	const char	*path;
// 	pid_t		pid;
// 	char		**argv;
// 	int			builtin_id;

// 	prepare_pipe(node);
// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		reset_signal();
// 		pipe_child(node);
// 		redirect(node->redirects);
// 		argv = tokens_to_argv(node->args);
// 		if (argv == NULL)
// 			return (1);
// 		path = argv[0];
// 		builtin_id = is_builtin(argv[0]);
// 		if (builtin_id > 0)
// 		{
// 			exec_builtin(builtin_id, argv);
// 			reset_redirect(node->redirects);
// 			fatal_error("builtin");
// 		}
// 		else
// 		{
// 			if (path && path[0] != '/' && path[0] != '.')
// 				path = search_path(argv[0]);
// 			validate_path(path, argv[0]);
// 			execve(path, argv, environ);
// 			reset_redirect(node->redirects);
// 			fatal_error("execve");
// 		}
// 	}
// 	else
// 	{
// 		pipe_parent(node);
// 		if (node->next)
// 			return (exec_pipe(node->next));
// 		return (pid);
// 	}
// }

int	exec(t_node *node)
{
	int			status;
	pid_t		last_pid;
	const char	*path;
	char		**argv;
	int			builtin_id;

	open_redir_file(node->redirects);
	argv = tokens_to_argv(node->args);
	if (argv == NULL)
		exit(1);
	path = argv[0];
	builtin_id = is_builtin(argv[0]);
	if (builtin_id > 0)
		status = exec_builtin_command(builtin_id, argv, node);
	else
	{
		last_pid = exec_pipe(node);
		status = wait_pipe(last_pid);
	}
	return (status);
}

void	interpret(char *line, int *g_last_status)
{
	t_token	*tokens;
	t_node	*node;

	tokens = tokenize(line);
	expand(tokens);
	if (tokens->type == TOKEN_EOF)
		;
	else if (g_syntax_error)
		*g_last_status = 2;
	else
	{
		node = parse(tokens);
		if (g_syntax_error)
			*g_last_status = 2;
		else
			*g_last_status = exec(node);
		free_node(node);
	}
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	// char		**environ;

	printf("envp:%p\n", envp);
	printf("envp:%s\n",*envp);
	if (!environ)
		environ = envp;
	printf("environ:%p\n",environ);
	printf("environ:%s\n",*environ);
	rl_outstream = stderr;
	g_last_status = 0;
	hashmap_create();
	environ_init();
	set_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_last_status);
		free(line);
	}
	hashmap_destroy(g_table);
	exit(g_last_status);
}

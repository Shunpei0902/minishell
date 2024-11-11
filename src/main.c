/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:31:38 by sasano            #+#    #+#             */
/*   Updated: 2024/04/07 14:36:12 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_path(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

char	*search_path(const char *filename)
{
	char	*string;
	char	*path;
	char	*value;

	path = getenv("PATH");
	while (*path)
	{
		value = ft_strchr(path, ':');
		if (value == NULL)
			value = path + ft_strlen(path);
		string = (char *)malloc(value - path + ft_strlen(filename) + 2);
		if (string == NULL)
			fatal_error("malloc");
		ft_strlcpy(string, path, value - path + 1);
		ft_strlcat(string, "/", value - path + 2);
		ft_strlcat(string, filename, value - path + ft_strlen(filename) + 2);
		if (access(string, X_OK) == 0)
			return (string);
		free(string);
		if (*value == '\0')
			break ;
		path = value + 1;
	}
	return (NULL);
}

char	**tokens_to_argv(t_token *tokens)
{
	char	**argv;
	int		argc;
	int		i;
	t_token	*current;

	argc = 0;
	current = tokens;
	while (current != NULL)
	{
		argc++;
		current = current->next;
	}
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		fatal_error("malloc");
	i = 0;
	while (i < argc)
	{
		argv[i] = tokens->value;
		i++;
		tokens = tokens->next;
	}
	argv[argc] = NULL;
	return (argv);
}

int wait_pipe(pid_t last_pid)
{
	pid_t wait_pid;
	int wstatus;
	int status;

	while (1)
	{
		wait_pid = wait(&wstatus);
		if (wait_pid == last_pid)
			status = WEXITSTATUS(wstatus);
		if (wait_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			fatal_error("wait");
		}
	}
	return (status);
}

pid_t	exec_pipe(t_node *node)
{
	extern char	**environ;
	const char	*path;
	pid_t		pid;
	char		**argv;

	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		pipe_child(node);
		redirect(node->redirects);
		argv = tokens_to_argv(node->args);
		path = argv[0];
		if (path[0] != '/' && path[0] != '.')
			path = search_path(argv[0]);
		validate_path(path, argv[0]);
		execve(path, argv, environ);
		reset_redirect(node->redirects);
		fatal_error("execve");
	}
	else
	{
		pipe_parent(node);
		if (node->next)
			return (exec_pipe(node->next));
		return (pid);
	}
}

int	exec(t_node *node)
{
	int	status;
	pid_t last_pid;

	open_redir_file(node->redirects);
	last_pid = exec_pipe(node);
	status = wait_pipe(last_pid);
	return (status);
}

void	interpret(char *line, int *status)
{
	t_token	*tokens;
	t_node	*node;

	tokens = tokenize(line);
	if (tokens->type == TOKEN_EOF)
		;
	else if (g_syntax_error)
		*status = 2;
	else
	{
		node = parse(tokens);
		if (g_syntax_error)
			*status = 2;
		else
			*status = exec(node);
		free_node(node);
	}
	free_tokens(tokens);
}

int	main(void)
{
	int status;
	char *line;

	rl_outstream = stderr;
	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &status);
		free(line);
	}
	exit(status);
}
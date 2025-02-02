/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:31:38 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 19:39:34 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_last_status;
t_bucket	*g_envmap[TABLESIZE];

static int	wait_status(int wstatus)
{
	int	status;

	status = 0;
	if (WIFEXITED(wstatus))
		status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(wstatus);
	return (status);
}

int	wait_pipe(pid_t last_pid)
{
	pid_t	wait_pid;
	int		wstatus;
	int		status;

	status = 0;
	while (1)
	{
		wait_pid = wait(&wstatus);
		set_signal();
		if (wait_pid == last_pid)
			status = wait_status(wstatus);
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

int	exec(t_node *node)
{
	int		status;
	pid_t	last_pid;
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		status = open_redir_file(tmp->redirects);
		if (status)
			return (status);
		tmp = tmp->next;
	}
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin(node);
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
		{
			expand(node);
			*g_last_status = exec(node);
		}
		free_node(node);
	}
	free_tokens(tokens);
}

int	main(void)
{
	char	*line;

	init_env();
	rl_outstream = stderr;
	g_last_status = 0;
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
	exit(g_last_status);
}

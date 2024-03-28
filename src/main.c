#include "minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	f(int i)
{
	(void)i;
	exit(0);
}

int	interpret(char *line)
{
	t_token		*tokens;
	extern char	**environ;
	pid_t		pid;
	int			wstatus;

	// char		*argv[] = {line, NULL};
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	free_tokens(tokens);
}

int	main(void)
{
	char *line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line);
		free(line);
	}
	exit(0);
}
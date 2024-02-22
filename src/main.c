#include "minishell.h"

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
		// TODO: intepret line as a command
		free(line);
	}
	exit(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:19 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/09 17:34:20 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

const char	*g_last_exit_status;

bool	isnum(char *av)
{
	while (*av)
		if (!ft_isdigit(*++av))
			return (false);
	return (true);
}

// todo("exit status of last command executed $?");
// printf("exit status of last command executed: %d\n",
// WEXITSTATUS(status)); // in pipe
int	b_exit(char **av)
{
	int	pid;

	if (av[1] == NULL)
	{
		return (0);
	}
	if (av[2] != NULL)
	{
		printf("exit: too many arguments");
		return (1);
	}
	if (!isnum(*av))
	{
		printf("exit: %s: numeric argument required\n", av[1]);
		return (2);
	}
	pid = ft_atoi(av[1]);
	if (kill(pid, SIGQUIT) == -1)
		return (1);
	return (pid);
}

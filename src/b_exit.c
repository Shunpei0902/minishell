/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:19 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/11 16:52:05 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

bool	isnum(char *av)
{
	while (*av)
		if (!ft_isdigit(*++av))
			return (false);
	return (true);
}

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

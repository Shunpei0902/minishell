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

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <stdint.h>

bool	isnum(char *av)
{
	while (*av)
		if (!ft_isdigit(*++av))
			return (false);
	return (true);
}

void set_cleanup_trap(void)
{
	hashmap_create();
}

void cleanup_and_exit(uint8_t exit_code)
{
	//TODO: trigger cleanup_trap;
	hashmap_destroy(g_table);
	g_readline_eof = true;
	exit(exit_code);
}

//TODO: on shell exit, hashmap_destroy();
/**
exit [n]
       Cause the shell to exit with a status of n.  If n is omitted, the exit status is that of the last command executed.  A trap on EXIT is executed before the shell
       terminates.
*/
void b_exit(char **av)
{
	uint8_t	pid;

	if (av[1] == NULL)
		cleanup_and_exit(g_last_status);
	if (av[2] != NULL)
	{
		// write(2, "exit: too many arguments", 23);
		// return (1);
		err_exit("exit", "too many arguments", 1);
	}
	if (!isnum(*av))
		err_exit("exit", "numeric argument required", 2);
	pid = (uint8_t)ft_atoi(av[1]);
	// if (kill(pid, SIGQUIT) == -1)
	// 	return (1);
	// return ((int)pid);
	cleanup_and_exit(pid);
}

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
#include <unistd.h>

bool	isnum(const char *str)
{
	size_t	i;

	i = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str[i] == '\0');
}

// void cleanup_and_exit(uint8_t exit_code)
void	cleanup_and_exit(int signo)
{
	(void)signo;
	hashmap_destroy(g_table);
	g_readline_eof = true;
}

void	set_cleanup_trap(void)
{
	struct sigaction	sa_usr1;

	sa_usr1.sa_handler = cleanup_and_exit;
	sigemptyset(&sa_usr1.sa_mask);
	sa_usr1.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1)
		err_exit("trap", "Failed to set SIGUSR1 handler", 1);
	hashmap_create();
}

// TODO: on shell exit, pass status value to g_last_status;
/**
exit [n]
		Cause the shell to exit with a status of n.  If n is omitted, the exit
status is that of the last command executed.  A trap on EXIT is executed before
the shell terminates.
*/
void	b_exit(char **av)
{
	uint8_t	status;

	if (av[1] == NULL)
	{
		status = g_last_status;
		// exit(g_last_status);
	}
	else if (av[2] != NULL)
	{
		// write(2, "exit: too many arguments", 23);
		// return (1);
		err_exit("exit", "too many arguments", 1);
	}
	else if (!isnum(av[1]))
		err_exit("exit", "numeric argument required", 2);
	else
		status = (uint8_t)ft_atoi(av[1]);
	if (kill(getppid(), SIGUSR1) == -1)
		err_exit("exit", "failed shell termination signal", status);
	// exit(pid);
	// cleanup_and_exit(pid);
}

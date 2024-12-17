/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:19 by niida             #+#    #+#             */
/*   Updated: 2024/12/17 13:51:41 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

// TODO: on shell exit, pass status to g_last_status and hashmap_destroy();
/**
exit [n]
		Cause the shell to exit with a status of n.  If n is omitted, the exit
status is that of the last command executed.  A trap on EXIT is executed before
the shell terminates.
*/
int	b_exit(char **av)
{
	uint8_t	status;

	if (av[1] == NULL)
		status = g_last_status;
	else if (av[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments", STDOUT_FILENO);
		return (1);
	}
	else if (!isnum(av[1]))
		err_exit("exit", "numeric argument required", 2);
	else
		status = (uint8_t)ft_atoi(av[1]);
	exit (status);
}

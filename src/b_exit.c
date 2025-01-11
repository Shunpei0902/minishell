/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:19 by niida             #+#    #+#             */
/*   Updated: 2025/01/12 00:59:14 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_strtol(const char *str)
{
	long long	ans;
	long		abs;

	ans = 0;
	abs = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			abs = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (abs == 1 && (ans > LONG_MAX / 10
				|| (ans == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10)))
			return (2);
		else if (abs == -1 && (-ans < LONG_MIN / 10
				|| (ans == -(LONG_MIN / 10) && (*str - '0') > -(LONG_MIN % 10))))
			return (2);
		ans = ans * 10 + (*str - '0');
		str++;
	}
	return ((int)(abs * ans));
}

bool	isnum(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
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
		ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	else if (!isnum(av[1]))
		err_exit("exit", "numeric argument required", 2);
	else
		status = (uint8_t)ft_strtol(av[1]);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:19 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/02 09:50:30 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isnum(char *av)
{
	if (*av == '-' || *av == '+')
		av++;
	if (!ft_isdigit(*av))
		return (false);
	while (*av)
	{
		if (!ft_isdigit(*av))
			return (false);
		av++;
	}
	return (true);
}

int	b_exit(char **av)
{
	int		res;
	char	*arg;

	if (av[1] == NULL)
		exit(g_last_status);
	if (av[2] != NULL)
	{
		error_message3("exit: ", "too many arguments", NULL);
		return (1);
	}
	arg = av[1];
	if (isnum(arg))
	{
		res = ft_atoi(arg);
		exit(res);
	}
	error_message3("exit: ", "numeric argument required: ", arg);
	exit(255);
}

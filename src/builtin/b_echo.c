/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:33:54 by niida             #+#    #+#             */
/*   Updated: 2025/01/23 22:20:23 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_option_n(char **av)
{
	char	*str;

	if (!av || !*av || **av != '-')
		return (true);
	str = *av + 1;
	while (*str == 'n')
		str++;
	if (*str)
		return (true);
	return (false);
}

int	b_echo(char **av)
{
	bool	op_newline;

	av++;
	op_newline = check_option_n(av);
	if (!op_newline)
		av++;
	while (*av)
	{
		write(1, *av, ft_strlen(*av));
		if (*(av + 1))
			write(1, " ", 1);
		av++;
	}
	if (op_newline)
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:33:54 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/11 16:11:30 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	b_echo(char **av)
{
	bool	op_newline;

	op_newline = true;
	if (*++av && ft_strncmp("-n", *av, 2) == 0)
	{
		op_newline = false;
		++av;
	}
	while (*av)
	{
		write(1, *av, strlen(*av));
		if (*(av + 1))
			write(1, " ", 1);
		++av;
	}
	if (op_newline)
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:54:55 by niida             #+#    #+#             */
/*   Updated: 2024/12/17 13:46:31 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// int b_env(void)
int	b_env(char **av)
{
	(void)av;
	while (*environ)
	{
		write(1, *environ, ft_strlen(*environ));
		write(1, "\n", 1);
		++environ;
	}
	return (0);
}

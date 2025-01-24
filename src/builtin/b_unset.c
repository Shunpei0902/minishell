/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:50:42 by niida             #+#    #+#             */
/*   Updated: 2025/01/24 18:05:09 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char **av)
{
	int	status;

	status = 0;
	av++;
	while (*av)
	{
		if (hash_unset(*av))
		{
			error_message("unset: ", "not a valid identifier");
			status = 1;
		}
		else
			status = 0;
		av++;
	}
	return (status);
}

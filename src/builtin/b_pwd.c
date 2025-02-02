/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:05:55 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 15:02:19 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(char **av)
{
	char	*pwd;

	(void)av;
	pwd = xgetenv("PWD");
	if (pwd == NULL)
	{
		perror("minishell");
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:05:55 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 22:06:17 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(char **av)
{
	char	*pwd;

	(void)av;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("minishell");
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

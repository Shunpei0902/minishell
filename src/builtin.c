/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:34:36 by niida             #+#    #+#             */
/*   Updated: 2024/12/17 13:51:41 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"

int	is_builtin(char *cmd)
{
	static char	*builtin[BUILT_IN_COUNT] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	int			i;

	i = BUILT_IN_COUNT;
	while (--i >= 0)
		if (ft_strncmp(cmd, builtin[i], ft_strlen(builtin[i])) == 0)
			return (i);
	return (-1);
}

int	exec_builtin(int i, char **cmd)
{
	static t_function	run[BUILT_IN_COUNT] = {
		b_echo,
		b_cd,
		b_pwd,
		b_export,
		b_unset,
		b_env,
		b_exit,
	};

	run[i](cmd);
	return (0);
}

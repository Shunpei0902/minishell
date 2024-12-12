/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:49:23 by niida             #+#    #+#             */
/*   Updated: 2024/04/13 17:00:51 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	b_cd(char **av)
{
	int		status;
	char	*path;

	path = *++av;
	if (!path)
		path = getenv("HOME");
	status = chdir(path);
	return (status);
}

int	b_pwd(char **av)
{
	char	*buf;

	(void)av;
	buf = getcwd(NULL, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (0);
}

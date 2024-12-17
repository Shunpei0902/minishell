/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:49:23 by niida             #+#    #+#             */
/*   Updated: 2024/12/17 13:43:50 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	b_cd(char **av)
{
	int		status;
	char	*path;
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	path = *++av;
	if (!path || *path == '~')
		path = getenv("HOME");
	status = chdir(path);
	if (status == 0)
	{
		pwd = getcwd(NULL, 0);
		ft_setenv("OLDPWD", old_pwd, 1);
		ft_setenv("PWD", pwd, 1);
		update_environ();
		free(pwd);
	}
	free(old_pwd);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:30 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 15:15:26 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(char *key, char *value)
{
	if (value == NULL)
		hash_put(key, "");
	else
		hash_put(key, value);
}

static int	error_retrieving(char *str, char *path)
{
	char	*tmp;

	if (!str)
	{
		error_message3("cd", "error retrieving current directory", NULL);
		tmp = xstrjoin("/", path);
		str = xstrjoin(xgetenv("OLDPWD"), tmp);
		update_env("PWD", str);
		free(tmp);
		free(str);
		return (1);
	}
	update_env("PWD", str);
	free(str);
	return (0);
}	

int	b_cd(char **av)
{
	char	*path;
	char	*str;

	update_env("OLDPWD", xgetenv("PWD"));
	if (av[1] == NULL)
	{
		path = xgetenv("HOME");
		if (path == NULL)
		{
			error_message3("cd", "HOME not set", NULL);
			return (1);
		}
	}
	else
		path = av[1];
	if (chdir(path) < 0)
	{
		error_message3("cd", av[1], ": No such file or directory");
		return (1);
	}
	str = getcwd(NULL, 0);
	return (error_retrieving(str, path));
}

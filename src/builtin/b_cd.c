/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:30 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 03:07:15 by sasano           ###   ########.fr       */
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
			error_message("cd", "HOME not set");
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
	update_env("PWD", str);
	free(str);
	return (0);
}

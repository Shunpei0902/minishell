/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:30 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 09:50:32 by sasano           ###   ########.fr       */
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
	update_env("PWD", str);
	free(str);
	return (0);
}

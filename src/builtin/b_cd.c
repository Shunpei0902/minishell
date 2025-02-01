/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:30 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 01:17:46 by sasano           ###   ########.fr       */
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

// static char	*get_newpwd(char *oldpwd, char *path)
// {
// 	char	newpwd[PATH_MAX];
// 	char	*dup;

// 	if (*path == '/' || oldpwd == NULL)
// 		ft_strlcpy(newpwd, "/", PATH_MAX);
// 	else
// 		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
// 	while (*path)
// 	{
// 		if (*path == '/')
// 			path++;
// 		else if (consume_path(&path, path, "."))
// 			;
// 		else if (consume_path(&path, path, ".."))
// 			delete_last_path_elm(newpwd);
// 		else
// 			append_path_elm(newpwd, PATH_MAX, &path, path);
// 	}
// 	dup = xstrdup(newpwd);
// 	return (dup);
// }

int	b_cd(char **av)
{
	char	*path;
	char	*str;
	char	*newpwd;

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
	update_env("PWD", getcwd(NULL, 0));
	return (0);
}

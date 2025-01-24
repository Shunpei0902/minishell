/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:30 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 22:24:22 by sasano           ###   ########.fr       */
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
	char	*pwd;
	char	*newpwd;

	pwd = xgetenv("PWD");
	update_env("OLDPWD", pwd);
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
	// newpwd = get_newpwd(path);
	// update_env("PWD", newpwd);
	update_env("PWD", getcwd(NULL, 0));
	return (0);
}

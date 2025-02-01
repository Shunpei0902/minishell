/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:49:19 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 18:57:16 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_path(const char *path, const char *filename)
{
	struct stat	st;

	if (path == NULL || *path == '\0' || ft_strcmp(filename, "..") == 0 ||
		access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
	if (stat(path, &st) < 0)
		fatal_error("fstat");
	if (S_ISDIR(st.st_mode))
		err_exit(filename, "is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit(path, "Permission denied", 126);
}

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*env_path;
	char	*value;

	if (filename == NULL || *filename == '\0')
		return (NULL);
	env_path = xgetenv("PATH");
	while (env_path && *env_path)
	{
		ft_bzero(path, PATH_MAX);
		value = ft_strchr(env_path, ':');
		if (value == NULL)
			value = env_path + ft_strlen(env_path);
		ft_strlcpy(path, env_path, value - env_path + 1);
		ft_strlcat(path, "/", value - env_path + 2);
		ft_strlcat(path, filename, value - env_path + ft_strlen(filename) + 2);
		if (access(path, F_OK) == 0)
			return (xstrdup(path));
		if (*value == '\0')
			break ;
		env_path = value + 1;
	}
	return (NULL);
}

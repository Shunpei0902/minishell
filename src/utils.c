/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:03:39 by sasano            #+#    #+#             */
/*   Updated: 2024/12/15 08:27:28 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_path(const char *path, const char *filename)
{
	struct stat	st;

	if (path == NULL || *path == '\0' || ft_strcmp(filename, "..") == 0
		|| access(path, F_OK) < 0)
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

	env_path = getenv("PATH");
	while (*env_path)
	{
		ft_bzero(path, PATH_MAX);
		value = ft_strchr(env_path, ':');
		if (value == NULL)
			value = env_path + ft_strlen(env_path);
		ft_strlcpy(path, env_path, value - env_path + 1);
		ft_strlcat(path, "/", value - env_path + 2);
		ft_strlcat(path, filename, value - env_path + ft_strlen(filename) + 2);
		if (access(path, F_OK) == 0)
			return (ft_strdup(path));
		if (*value == '\0')
			break ;
		env_path = value + 1;
	}
	return (NULL);
}

char	**tokens_to_argv(t_token *tokens)
{
	char	**argv;
	int		argc;
	int		i;
	t_token	*current;

	argc = 0;
	current = tokens;
	while (current != NULL)
	{
		argc++;
		current = current->next;
	}
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		fatal_error("malloc");
	i = 0;
	while (i < argc)
	{
		argv[i] = tokens->value;
		i++;
		tokens = tokens->next;
	}
	argv[argc] = NULL;
	return (argv);
}

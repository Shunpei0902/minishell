/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:03:39 by sasano            #+#    #+#             */
/*   Updated: 2024/12/12 23:12:36 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_path(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

char	*search_path(const char *filename)
{
	char	*string;
	char	*path;
	char	*value;

	path = getenv("PATH");
	while (*path)
	{
		value = ft_strchr(path, ':');
		if (value == NULL)
			value = path + ft_strlen(path);
		string = (char *)malloc(value - path + ft_strlen(filename) + 2);
		if (string == NULL)
			fatal_error("malloc");
		ft_strlcpy(string, path, value - path + 1);
		ft_strlcat(string, "/", value - path + 2);
		ft_strlcat(string, filename, value - path + ft_strlen(filename) + 2);
		if (access(string, X_OK) == 0)
			return (string);
		free(string);
		if (*value == '\0')
			break ;
		path = value + 1;
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

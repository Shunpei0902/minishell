/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:33:06 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 02:43:29 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	extern char	**environ;
	int			i;
	char		*key;
	char		*value;

	i = 0;
	while (environ[i])
	{
		key = xstrcdup(environ[i], '=');
		value = ft_strchr(environ[i], '=') + 1;
		hash_put(key, value);
		free(key);
		i++;
	}
	if (hash_get("SHLVL") == NULL)
		hash_put("SHLVL", "1");
	if (hash_get("PWD") == NULL)
		hash_put("PWD", getcwd(NULL, 0));
}

char	*xgetenv(const char *name)
{
	t_bucket	*bucket;

	bucket = hash_get(name);
	if (bucket)
		return (bucket->value);
	return (NULL);
}

static char	**get_env_from_bucket(char **env, t_bucket *bucket, int *num)
{
	char *tmp;
	while (bucket)
	{
		tmp = xstrjoin(bucket->key, "=");
		env[*num] = tmp;
		env[*num] = xstrjoin(env[*num], bucket->value);
		free(tmp);
		bucket = bucket->next;
		(*num)++;
	}
	return (env);
}

char	**get_environ(void)
{
	char	**env;
	int		i;
	int		num;
	int		size;

	size = hash_num();
	env = xcalloc(size + 1, sizeof(char *));
	i = 0;
	num = 0;
	while (i < TABLESIZE)
	{
		if (g_envmap[i] && g_envmap[i]->key)
			get_env_from_bucket(env, g_envmap[i], &num);
		i++;
	}
	env[num] = NULL;
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:33:06 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 17:45:25 by sasano           ###   ########.fr       */
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
		// printf("environ[%d]: %s\n", i, environ[i]);
		key = xstrcdup(environ[i], '=');
		value = ft_strchr(environ[i], '=') + 1;
		// printf("key: %s\n", key);
		hash_put(key, value);
		free(key);
		i++;
	}
	if (hash_get("SHLVL") == NULL)
		hash_put("SHLVL", "1");
	if (hash_get("PWD") == NULL)
		hash_put("PWD", getcwd(NULL, 0));
	hash_unset("OLDPWD");
	// hash_put("OLDPWD", "");
	// hash_unset("IFS");
	// hash_put("IFS", " \t\n");
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
	while (bucket)
	{
		env[*num] = xstrjoin(bucket->key, "=");
		env[*num] = xstrjoin(env[*num], bucket->value);
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
			env = get_env_from_bucket(env, g_envmap[i], &num);
		i++;
	}
	env[num] = NULL;
	return (env);
}

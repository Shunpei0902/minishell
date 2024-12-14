/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:35 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/11 16:24:42 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
GETENV(3)
The	setenv(void) function inserts or resets the environment variable name in the
current environment list.
If the variable name does not exist in the list,
it is inserted with the given value.
If the variable does exist, the argument overwrite is tested;
if overwrite is zero, the variable is not reset,
otherwise it is reset to the given value.
*/
int	ft_setenv(const char *name, const char *value, int overwrite)
{
	int			index;
	t_bucket	*curr;

	if (!g_table)
		fatal_error("hashtable not found");
	index = hash(name);
	curr = g_table->entries[index];
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
		{
			if (overwrite != 0)
				curr->value = ft_strdup(value);
			return (0);
		}
		curr = curr->next;
	}
	curr = malloc(sizeof(t_bucket));
	if (!curr)
		fatal_error("variable allocation error");
	curr->key = ft_strdup(name);
	curr->value = ft_strdup(value);
	curr->next = NULL;
	g_table->var_count++;
	return (0);
}

t_bucket	*get_key_value(const char *str)
{
	t_bucket		*pair;
	const char		*cpy;
	unsigned int	len;

	len = 0;
	cpy = str;
	pair = malloc(sizeof(t_bucket));
	while (*cpy)
	{
		if (*cpy++ == '=')
			break ;
		len++;
	}
	pair->key = malloc(sizeof(char *) * len + 1);
	if (!pair->key)
		fatal_error("variable key name allocation error");
		// return (NULL);
	ft_strlcpy(pair->key, str, len + 1);
	pair->value = ft_strdup(cpy);
	return (pair);
}

int	environ_init(void)
{
	int			i;
	char		**av;
	t_bucket	*pair;

	i = 0;
	av = environ;
	pair = malloc(sizeof(t_bucket));
	if (!pair)
		return (1);
	while (av[++i])
	{
		pair = get_key_value(av[i++]);
		ft_setenv(pair->key, pair->value, 1);
	}
	update_environ();
	return (0);
}

void b_export(char **av)
{
	char		**env;
	t_bucket	*pair;
	int			i;

	i = 1;
	env = environ;
	if (av[1] == NULL)
	{
		while (*env)
		{
			write(1, "declare -x ", 11);
			write(1, *env, ft_strlen(*env));
			write(1, "\n", 1);
			env++;
		}
		exit(0);
	}
	pair = malloc(sizeof(t_bucket));
	if (!pair)
		err_exit("export", "variable allocation error", errno);
	while (av[i])
	{
		pair = get_key_value(av[i++]);
		ft_setenv(pair->key, pair->value, 1);
	}
	exit(0);
}

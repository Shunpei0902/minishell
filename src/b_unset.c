/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:50:42 by niida             #+#    #+#             */
/*   Updated: 2024/12/09 21:38:50 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "hashmap.h"

t_hashmap	*g_table = NULL;

// char **:
// void set_environ_line(void *node)
// char *set_environ_line(t_node *node)
// {
// 	char *line;
// 	t_node *bucket = (t_node *)node;

// 	while (bucket)
// 	{
// 		line = ft_strjoin(bucket->key, "=");
// 		line = ft_strjoin(line, bucket->value);
// 		if (!line)
// 			return (NULL);
// 		bucket = bucket->next;
// 	}

// }

void	update_environ(void)
{
	int		i;
	int		j;
	char	**new;
	t_node	*bucket;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * g_table->var_count);
	if (!new)
		return ;
	while (i < TABLESIZE)
	{
		bucket = g_table->entries[i];
		while (bucket)
		{
			new[j] = ft_strjoin(bucket->key, "=");
			new[j] = ft_strjoin(new[j], bucket->value);
			if (!new[j])
				return ;
			bucket = bucket->next;
			j++;
		}
		i++;
	}
}

// /**
// GETENV(3)
// The	setenv(void) function inserts or resets the
// environment variable name in the current environment list.
// If the variable name does not exist in the list,
// it is inserted with the given value.
// If the variable does exist, the argument overwrite is tested;
// if overwrite is zero, the variable is not reset,
// otherwise it is reset to the given value.
// */
// int	ft_setenv(const char *name, const char *value, int overwrite)
// {
// 	int		index;
// 	t_node	*curr;

// 	index = hash(name);
// 	curr = table->entries[index];
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, name) == 0)
// 		{
// 			if (overwrite != 0)
// 				curr->value = ft_strdup(value);
// 			return (0);
// 		}
// 		curr = curr->next;
// 	}
// 	curr = malloc(sizeof(t_node));
// 	if (!curr)
// 		return (-1);
// 	curr->key = ft_strdup(name);
// 	curr->value = ft_strdup(value);
// 	curr->next = NULL;
// 	table->var_count++;
// 	return (0);
// }

/**
GETENV(3)
The	unsetenv(void) function deletes all instances of the variable name pointed
to by name from the list.  Note that only the variable name (e.g., "NAME")
should be given; "NAME=value" will not work.
*/
int	ft_unsetenv(const char *name)
{
	int		index;
	t_node	*curr;
	t_node	*prev;

	index = hash(name);
	curr = g_table->entries[index];
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(name, curr->key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				g_table->entries[index] = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			g_table->var_count--;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	b_unset(char **av)
{
	while (*av)
		ft_unsetenv(*av++);
	update_environ();
	return (0);
}

// t_node	*get_key_value(const char *str)
// {
// 	t_node			*pair;
// 	const char		*cpy;
// 	unsigned int	len;

// 	len = 0;
// 	cpy = str;
// 	pair = malloc(sizeof(t_node));
// 	while (*cpy)
// 	{
// 		if (*cpy++ != '=')
// 		{
// 			len++;
// 			break ;
// 		}
// 	}
// 	pair->key = malloc(sizeof(char *) * len);
// 	if (!pair->key)
// 		return (NULL);
// 	ft_strlcpy(pair->key, str, len);
// 	pair->value = ft_strdup(cpy);
// 	return (pair);
// }

// // [name[=value] ...]
// // todo: convert my hash table into char ** and newly point environ to it so
// // other subprocesses and c programs
// // int	environ_init(t_hashmap *table, const char **environ)
// int	environ_init(void)
// {
// 	int		i;
// 	char	**av;
// 	t_node	*pair;

// 	i = 0;
// 	av = environ;
// 	pair = malloc(sizeof(t_node));
// 	while (av[++i])
// 	{
// 		pair = get_key_value(av[i++]);
// 		ft_setenv(pair->key, pair->value, 1);
// 	}
// 	update_environ();
// 	return (0);
// }

// moved to b_export.c
//  int	b_export(char **av)
//  {
//  	char	**env;
//  	t_node	*pair;
//  	int		i;

// 	i = 1; // TODO: may need fix to i = 0;
// 	env = environ;
// 	if (av[1] == NULL)
// 	{
// 		while (*env)
// 		{
// 			write(1, "declare -x ", 11);
// 			write(1, *env, strlen(*env));
// 			write(1, "\n", 1);
// 			env++;
// 		}
// 		return (0);
// 	}
// 	pair = malloc(sizeof(t_node));
// 	while (av[i])
// 	{
// 		pair = get_key_value(av[i++]);
// 		ft_setenv(pair->key, pair->value, 1);
// 	}
// 	return (0);
// }

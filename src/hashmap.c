/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:28:47 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/09 21:28:48 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"

// t_hashmap	*table = NULL;

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return ((unsigned int)*str1 - (unsigned int)*str2);
		str1++;
		str2++;
	}
	return (0);
}

int	hash(const char *key)
{
	int	code;

	code = 0;
	while (*key)
		code += (int)*key++;
	return (code % TABLESIZE);
}

t_hashmap *hashmap_create(void)
{
    int i;

    g_table = malloc(sizeof(t_hashmap));
    if (!g_table)
        return NULL;
    i = 0;
    while (i < TABLESIZE)
        g_table->entries[i++] = NULL;
    g_table->var_count = 0;
    return g_table;
}

// t_hashmap	*hashmap_create(void)
// {
// 	t_hashmap	*table;

// 	table = malloc(sizeof(t_hashmap));
// 	table->var_count = 0;
// 	return (table);
// }

// void	hashmap_put(t_hashmap *map, const char *key, const char *value)
// {
// 	int		index;
// 	t_node	*node;

// 	index = hash(key);
// 	node = map->entries[index];
// 	while (node)
// 	{
// 		if (ft_strcmp(node->key, key) == 0)
// 		{
// 			node->value = ft_strdup(value);
// 			return ;
// 		}
// 		node = node->next;
// 	}
// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 		return ;
// 	node->key = ft_strdup(key);
// 	node->value = ft_strdup(value);
// 	node->next = NULL;
// }

// char	*hashmap_get(t_hashmap *map, const char *key)
// {
// 	int		index;
// 	t_node	*curr;

// 	index = hash(key);
// 	curr = map->entries[index];
// 	while (curr)
// 	{
// 		if (ft_strcmp(key, curr->key))
// 		{
// 			return (curr->value);
// 		}
// 		curr = curr->next;
// 	}
// 	return (NULL);
// }

// void	hashmap_remove(t_hashmap *map, const char *key)
// {
// 	int		index;
// 	t_node	*curr;
// 	t_node	*prev;

// 	index = hash(key);
// 	curr = map->entries[index];
// 	prev = NULL;
// 	while (curr)
// 	{
// 		if (!prev)
// 			prev = map->entries[index];
// 		else
// 			prev->next = curr->next;
// 		if (ft_strcmp(key, curr->key) == 0)
// 		{
// 			map->entries[index] = curr->next;
// 			free(curr->key);
// 			free(curr->value);
// 			free(curr->next);
// 			curr = NULL;
// 			return ;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }

// void	hashmap_destroy(t_hashmap *map)
// {
// 	int		index;
// 	t_node	*curr;
// 	t_node	*tmp;

// 	index = -1;
// 	while (++index < TABLESIZE)
// 	{
// 		curr = map->entries[index];
// 		tmp = NULL;
// 		while (curr)
// 		{
// 			tmp = curr->next;
// 			free(curr->key);
// 			free(curr->value);
// 			free(curr->next);
// 			curr = tmp;
// 		}
// 	}
// 	free(map);
// 	map = NULL;
// }

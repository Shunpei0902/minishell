/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:28:47 by naokiiida         #+#    #+#             */
/*   Updated: 2025/01/24 19:19:33 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bucket	*hash_get(const char *key)
{
	unsigned int	index;
	t_bucket		*tmp;

	index = hash(key);
	tmp = g_envmap[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	hash_put(const char *key, const char *value)
{
	int			index;
	t_bucket	*tmp;
	t_bucket	*new_node;

	index = hash(key);
	tmp = g_envmap[index];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			if (value)
				tmp->value = xstrdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = xmalloc(sizeof(t_bucket));
	new_node->key = xstrdup(key);
	new_node->value = xstrdup(value);
	new_node->next = g_envmap[index];
	g_envmap[index] = new_node;
}

int	hash_unset(const char *key)
{
	unsigned int	index;
	t_bucket		*tmp;
	t_bucket		*prev;

	index = hash(key);
	tmp = g_envmap[index];
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			// printf("key: %s\n", tmp->key);
			if (prev == NULL)
				g_envmap[index] = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	hash_num(void)
{
	int			i;
	int			num;
	t_bucket	*tmp;

	i = 0;
	num = 0;
	while (i < TABLESIZE)
	{
		if (g_envmap[i] && g_envmap[i]->key)
		{
			num++;
			tmp = g_envmap[i];
			while (tmp->next)
			{
				num++;
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (num);
}

unsigned int	hash(const char *key)
{
	unsigned int	hashvalue;

	hashvalue = 0;
	while (*key)
		hashvalue = (hashvalue * 31 + *key++) % TABLESIZE;
	return (hashvalue);
}

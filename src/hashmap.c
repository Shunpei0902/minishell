/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:28:47 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/11 16:33:49 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"

t_hashmap	*g_table = NULL;

void	update_environ(void)
{
	int			i;
	int			j;
	char		**new;
	t_bucket	*bucket;

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

t_hashmap	*hashmap_create(void)
{
	int	i;

	g_table = malloc(sizeof(t_hashmap));
	if (!g_table)
		return (NULL);
	i = 0;
	while (i < TABLESIZE)
		g_table->entries[i++] = NULL;
	g_table->var_count = 0;
	return (g_table);
}

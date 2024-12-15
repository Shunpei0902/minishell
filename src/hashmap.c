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
char		**environ;

void	update_environ(void)
{
	int			i;
	int			j;
	char		**new;
	char		*tmp;
	t_bucket	*bucket;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (g_table->var_count + 1));
	if (!new)
		return ;
	while (i < TABLESIZE)
	{
		bucket = g_table->entries[i];
		while (bucket)
		{
			// printf("bucket key:%s, value:%s\n", bucket->key, bucket->value);
			tmp = ft_strjoin(bucket->key, "=");
			new[j] = ft_strjoin(tmp, bucket->value);
			free(tmp);
			if (!new[j])
			{
			    while (--j >= 0)
                    free(new[j]);
                free(new);
                return ;
			}
			printf("new[%d]:%s\n", j, new[j]);
			bucket = bucket->next;
			j++;
		}
		i++;
	}
	// new[j] = NULL;
	// environ = new;
    new[j] = NULL;
    printf("environ before points to: %p\n", (void*)environ);
    printf("Before updating environ: %s\n", getenv("PWD"));
    environ = new;
    printf("After updating environ: %s\n", getenv("PWD"));
    printf("environ now points to: %p\n", (void*)environ);
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

void	hashmap_destroy(t_hashmap *map)
{
	int			index;
	t_bucket	*curr;
	t_bucket	*tmp;

	index = -1;
	while (++index < TABLESIZE)
	{
		curr = map->entries[index];
		tmp = NULL;
		while (curr)
		{
			tmp = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr->next);
			curr = tmp;
		}
	}
	free(map);
	map = NULL;
}

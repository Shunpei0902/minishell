/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:28:57 by naokiiida         #+#    #+#             */
/*   Updated: 2024/12/09 21:28:58 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H
# define BUILT_IN_COUNT 7
# define TABLESIZE 100

typedef struct node
{
	char			*key;
	char			*value;
	struct node		*next;
}					t_node;

typedef struct hashmap
{
	t_node			*entries[TABLESIZE];
	unsigned int	var_count;
}					t_hashmap;

extern t_hashmap	*g_table;

int					ft_strcmp(const char *str1, const char *str2);
t_hashmap			*hashmap_create(void);
int					hash(const char *key);
void				hashmap_put(t_hashmap *map, const char *key,
						const char *value);
char				*hashmap_get(t_hashmap *map, const char *key);
void				hashmap_remove(t_hashmap *map, const char *key);
void				hashmap_destroy(t_hashmap *map);

#endif

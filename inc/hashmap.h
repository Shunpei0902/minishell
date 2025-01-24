/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:28:57 by naokiiida         #+#    #+#             */
/*   Updated: 2025/01/24 17:08:08 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H
# define BUILT_IN_COUNT 7
# define TABLESIZE 512

# include <stdbool.h>

typedef struct bucket
{
	char			*key;
	char			*value;
	struct bucket	*next;
}					t_bucket;

void				init_env(void);
t_bucket			*hash_get(const char *key);
void				hash_put(const char *key, const char *value);
int					hash_unset(const char *key);
int					hash_num(void);
unsigned int		hash(const char *key);

char				**get_environ(void);
void				init_env(void);
char				*xgetenv(const char *name);

int					ft_strcmp(const char *str1, const char *str2);
bool				is_identifier(const char *s);

#endif

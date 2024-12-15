/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:50:42 by niida             #+#    #+#             */
/*   Updated: 2024/12/11 16:34:00 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"

/**
GETENV(3)
The	unsetenv(void) function deletes all instances of the variable name pointed
to by name from the list.  Note that only the variable name (e.g., "NAME")
should be given; "NAME=value" will not work.
*/
int	ft_unsetenv(const char *name)
{
	int			index;
	t_bucket	*curr;
	t_bucket	*prev;

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
	while (*++av)
		ft_unsetenv(*av);
	update_environ();
	return (0);
}

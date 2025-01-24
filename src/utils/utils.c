/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:03:39 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 17:42:37 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_argv(t_token *tokens)
{
	char	**argv;
	int		argc;
	int		i;
	t_token	*current;

	argc = 0;
	current = tokens;
	while (current != NULL)
	{
		argc++;
		current = current->next;
	}
	argv = xcalloc(argc + 1, sizeof(char *));
	i = 0;
	while (i < argc)
	{
		argv[i] = tokens->value;
		i++;
		tokens = tokens->next;
	}
	argv[argc] = NULL;
	return (argv);
}

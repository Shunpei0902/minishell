/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:34:35 by niida             #+#    #+#             */
/*   Updated: 2025/02/02 03:49:59 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(void)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (i < TABLESIZE)
	{
		if (g_envmap[i])
		{
			key = g_envmap[i]->key;
			value = g_envmap[i]->value;
			if (ft_strcmp(key, "_") != 0)
			{
				printf("declare -x %s", key);
				if (value)
					printf("=\"%s\"", value);
				printf("\n");
			}
		}
		i++;
	}
}

static void	case_no_equal(char *key)
{
	t_bucket	*bucket;

	bucket = hash_get(key);
	if (bucket == NULL)
	{
		hash_put(key, NULL);
		return ;
	}
}

static int	add_env(char *av)
{
	char	*key;
	char	*value;

	key = xstrcdup(av, '=');
	if (!is_identifier(key))
	{
		free(key);
		error_message("export", "not a valid identifier");
		return (1);
	}
	value = ft_strchr(av, '=');
	if (value == NULL)
		case_no_equal(key);
	else
		hash_put(key, ++value);
	free(key);
	return (0);
}

int	b_export(char **av)
{
	int	status;

	av++;
	if (av == NULL || *av == NULL)
	{
		print_env();
		return (0);
	}
	while (*av)
	{
		status = add_env(*av);
		if (status)
			return (status);
		av++;
	}
	return (0);
}

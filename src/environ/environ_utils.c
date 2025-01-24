/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:29:27 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 18:13:54 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alpha_under(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

static bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || (c >= '0' && c <= '9'));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	if (!str1 || !str2)
	{
		return (1);
	}
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
			return ((unsigned int)*str1 - (unsigned int)*str2);
		str1++;
		str2++;
	}
	return (0);
}

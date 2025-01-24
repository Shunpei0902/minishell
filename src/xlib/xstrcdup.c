/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrcdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:02:50 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 19:13:16 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrcdup(const char *str, int c)
{
	char	*dst;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	dst = xmalloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

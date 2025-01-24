/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:44:22 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 15:41:03 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_strdup(s);
	if (!str)
		fatal_error("strdup failed");
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:42:50 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 19:28:45 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrjoin(char *s1, char *s2)
{
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	new = ft_strjoin(s1, s2);
	if (new == NULL)
		fatal_error("ft_strjoin");
	return (new);
}

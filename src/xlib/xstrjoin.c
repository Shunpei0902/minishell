/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:42:50 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 19:11:55 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrjoin(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (new == NULL)
		fatal_error("ft_strjoin");
	return (new);
}

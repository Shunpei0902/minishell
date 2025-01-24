/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:00:51 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 18:46:29 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		fatal_error("malloc failed");
	return (ptr);
}

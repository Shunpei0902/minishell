/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:36:01 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 19:12:40 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
		fatal_error("calloc failed");
	return (ptr);
}

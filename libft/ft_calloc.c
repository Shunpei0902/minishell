/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:45:58 by sasano            #+#    #+#             */
/*   Updated: 2023/10/17 00:23:33 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (size && n > SIZE_MAX / size)
		return (NULL);
	if (n == 0 || size == 0)
	{
		n = 1;
		size = 1;
	}
	ptr = malloc(n * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, n * size);
	return (ptr);
}
/*
int	main(void)
{
	int	*x;
	int	*y;
	int	i;

	x = calloc(-2147483648, -2147483648);
	y = ft_calloc(2147483648, 2147483648);
	i = 0;
	while (i < 1)
	{
		printf("%d", x[i]);
		i++;
	}
	printf("\n");
	free(x);
	i = 0;
	while (i < 1)
	{
		printf("%d", y[i]);
		i++;
	}
	printf("\n");
	free(y);
	return (0);
}
 */
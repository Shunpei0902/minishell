/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:36:38 by sasano            #+#    #+#             */
/*   Updated: 2023/11/10 01:19:25 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cat(char *dest, const char *src, unsigned int size)
{
	int	op;

	op = size;
	while (size > 1 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		size--;
	}
	if (op)
		*dest = '\0';
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ini_size;

	if (size == 0 && src)
		return (ft_strlen(src));
	i = ft_strlen(dest);
	j = ft_strlen(src);
	ini_size = size;
	while (*dest && size > 0)
	{
		dest++;
		size--;
	}
	cat(dest, src, size);
	if (ini_size <= i)
		return ((ini_size + j));
	return (i + j);
}
/*
int	main(void)
{
	char			dest[20];
	char			src[20];
	int				x;
	unsigned int	result1;
	unsigned int	result2;

	strcpy(dest, "123456");
	strcpy(src, "1234");
	x = 0;
	result1 = ft_strlcat(dest, src, x);
	printf("%s: %u\n", dest, result1);
	strcpy(dest, "123456");
	strcpy(src, "1234");
	result2 = strlcat(dest, src, x);
	printf("%s: %u\n", dest, result2);
	return (0);
} */

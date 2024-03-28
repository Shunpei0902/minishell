/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:45:05 by sasano            #+#    #+#             */
/*   Updated: 2023/10/17 06:33:24 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *dest, char const *src, size_t n)
{
	size_t	i;

	if (!*src)
		return ((char *)dest);
	while (n && *dest)
	{
		if (*dest == *src)
		{
			i = 0;
			while (src[i] && dest[i] == src[i] && i < n)
				i++;
			if (!src[i])
				return ((char *)dest);
		}
		dest++;
		n--;
	}
	return (0);
}
/*
int	main(void)
{
	char	buf[20];
	char	buf2[20];

	strcpy(buf, "aaabcabcd");
	strcpy(buf2, "aabc");
	printf("%s\n", strnstr(buf, buf, -1));
	printf("%s\n", ft_strnstr(buf, buf, -1));
	return (0);
} */

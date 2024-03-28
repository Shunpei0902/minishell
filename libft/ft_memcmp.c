/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:52:26 by sasano            #+#    #+#             */
/*   Updated: 2023/10/29 13:49:57 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
/*
int	main(void)
{
	char	buf[20];
	char	buf2[20];

	strcpy(buf, "123456789");
	strcpy(buf2, "1234123456789");
	printf("%d\n", memcmp(buf, buf2, 4));
	printf("%d\n", ft_memcmp(buf, buf2, 4));
	return (0);
}
 */
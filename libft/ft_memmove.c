/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:59:35 by sasano            #+#    #+#             */
/*   Updated: 2023/09/29 18:21:07 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	buf[20];

	strcpy(buf, "123456789");
	printf("%s\n", ft_memmove(buf + 3, buf, 5));
	printf("%s\n", memmove(buf + 3, buf, 5));
	return (0);
} */

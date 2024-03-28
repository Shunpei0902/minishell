/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:40:24 by sasano            #+#    #+#             */
/*   Updated: 2023/10/26 21:46:04 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *buf, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)buf == (unsigned char)c)
			return ((unsigned char *)buf);
		buf++;
	}
	return (0);
}

/* int	main(void)
{
	char	buf[20];

	strcpy(buf, "123456789");
	printf("%s\n", memchr(buf, '5', 3));
	printf("%s\n", ft_memchr(buf, '5', 3));
	return (0);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:48:05 by sasano            #+#    #+#             */
/*   Updated: 2023/10/06 12:17:02 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	void	*tmp;

	tmp = dest;
	if (!n || dest == src)
		return (dest);
	while (n--)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
	}
	return (tmp);
}

/* int	main(void)
{
	char	buf[20];
	char	buf2[20];

	strcpy(buf, "ABCDEFGHIJK");
	strcpy(buf2, "123456789");
	printf("%s\n", ft_memcpy(buf + 3, buf, 5));
	printf("%s\n", memcpy(buf + 3, buf, 5));
	return (0);
}
 */
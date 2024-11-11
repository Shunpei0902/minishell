/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:35 by sasano            #+#    #+#             */
/*   Updated: 2023/10/19 22:43:42 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	void	*tmp;

	tmp = dest;
	while (count--)
	{
		*(unsigned char *)dest = (unsigned char)c;
		dest++;
	}
	return (tmp);
}

/* int	main(void)
{
	char	buf[20];

	strcpy(buf, "ABCDEFGHIJK");
	printf("%s\n", buf);
	printf("%s\n", ft_memset(buf, '1', 3));
	printf("%s\n", memset(buf, '2', 2));
	return (0);
}
 */
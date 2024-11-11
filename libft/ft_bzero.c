/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:23 by sasano            #+#    #+#             */
/*   Updated: 2023/10/26 21:18:37 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	while (n--)
		*(unsigned char *)dest++ = 0;
}

/* int	main(void)
{
	char	buf[20];

	strcpy(buf, "ABCDEFGHIJK");
	ft_bzero(buf + 5, 0);
	bzero(buf, 0);
	printf("%s\n", buf);
	return (0);
} */

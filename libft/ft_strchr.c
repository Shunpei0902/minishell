/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:55:32 by sasano            #+#    #+#             */
/*   Updated: 2023/10/29 13:58:10 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *dest, int c)
{
	while (*dest)
	{
		if (*dest == (char)c)
			return ((char *)dest);
		dest++;
	}
	if (c == 0)
		return ((char *)dest);
	return (0);
}
/*
int	main(void)
{
	char	buf[20];

	strcpy(buf, "123456789");
	printf("%s\n", ft_strchr(buf, 'a'));
	printf("%s\n", strchr(buf, 'a'));
	return (0);
} */

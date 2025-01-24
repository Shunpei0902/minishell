/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:11:28 by sasano            #+#    #+#             */
/*   Updated: 2025/01/23 22:16:29 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *src)
{
	int		i;
	char	*p;
	char	*cpy;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
		i++;
	cpy = (char *)malloc(i + 1);
	if (!cpy)
		return (NULL);
	p = cpy;
	while (*src)
	{
		*cpy = *src;
		cpy++;
		src++;
	}
	*cpy = '\0';
	return (p);
}
/*
int	main(void)
{
	char	*str;
	char	*src;
	char	dest[20];

	strcpy(dest, "jclkbwv");
	src = strdup(dest);
	str = ft_strdup(dest);
	printf("%s\n", str);
	printf("%s\n", src);
	return (0);
}
 */
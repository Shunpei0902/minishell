/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano.stu>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:35:55 by sasano            #+#    #+#             */
/*   Updated: 2023/11/10 01:20:38 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i == size - 1 || src[i] == '\0')
		{
			dest[i] = '\0';
			break ;
		}
		dest[i] = src[i];
		i++;
	}
	return (ft_strlen(src));
}
/*
int	main(void)
{
	unsigned int	i;
	char			dest[10];

	i = ft_strlcpy(dest, "kbs", 10);
	printf("%d,%s", i, dest);
	return (0);
}
 */
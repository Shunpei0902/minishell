/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:29:07 by sasano            #+#    #+#             */
/*   Updated: 2023/10/29 14:01:00 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*overstart(void)
{
	char	*substr;

	substr = (char *)malloc(sizeof(char) * 1);
	if (!substr)
		return (NULL);
	substr[0] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*substr;

	if (!s)
		return (0);
	len_s = ft_strlen((char *)s);
	if (len_s < start || len == 0)
		return (overstart());
	if (len_s < len + start)
		len = len_s - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int	main(void)
{
	char	*s;
	char	*substr;

	s = "Hello World";
	substr = ft_substr(s, 1, 1);
	printf("%s\n", substr);
	return (0);
}
 */
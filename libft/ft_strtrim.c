/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:03:49 by sasano            #+#    #+#             */
/*   Updated: 2023/10/29 14:00:49 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strsetlen(char *s1, char *set)
{
	int		len;
	char	*start;

	len = 0;
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
	}
	if (*s1 == '\0')
		return (len);
	start = s1;
	while (*s1)
		s1++;
	while (ft_strrchr(set, *s1))
		s1--;
	while (start <= s1)
	{
		len++;
		start++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (0);
	len = ft_strsetlen((char *)s1, (char *)set);
	if (len == 0 || *s1 == '\0')
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (ft_strchr(set, *s1))
		s1++;
	i = 0;
	while (i < len)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

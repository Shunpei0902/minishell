/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:28:13 by sasano            #+#    #+#             */
/*   Updated: 2023/10/19 22:56:20 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	ans;
	long	abs;

	ans = 0;
	abs = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			abs = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (ans > (__LONG_MAX__ - (*str - '0')) / 10 && abs == 1)
			return ((int)__LONG_MAX__);
		else if (ans > ((__LONG_MAX__) - (*str - '0')) / 10 && abs == -1)
			return ((int)(__LONG_MAX__ * -1 - 1));
		ans = ans * 10 + (*str - '0');
		str++;
	}
	return ((int)(abs * ans));
}

/* int	main(void)
{
	printf("%d\n", atoi("    00000000009223372036854775807"));
	printf("%d\n", ft_atoi("   0000000009223372036854775807"));
	return (0);
} */

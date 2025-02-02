/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:25:19 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 14:43:03 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word_non_sym(char *value, char *line, int *i)
{
	char	*tmp;
	char	*tmp1;

	tmp = get_word(line, i);
	tmp1 = ft_strjoin(value, tmp);
	if (tmp)
		free(tmp);
	if (value)
		free(value);
	return (tmp1);
}

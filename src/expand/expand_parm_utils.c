/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parm_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:00:02 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 13:44:12 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_isalpha_isunder(char str)
{
	if (ft_isalpha(str) || ft_isdigit(str) || str == '_')
		return (str);
	return (0);
}

char	*get_env(char *line, int *i, int *start)
{
	char	*tmp;
	char	*tmp1;

	*start = *i;
	if (line[*start] != '$')
		return (NULL);
	if (check_isalpha_isunder(line[*i + 1]) == 0 && line[*i + 1] != '?')
	{
		(*i)++;
		return (ft_substr(line, *start, 1));
	}
	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_last_status));
	}
	while (check_isalpha_isunder(line[*i]))
		(*i)++;
	tmp = ft_substr(line, *start + 1, *i - *start - 1);
	tmp1 = xgetenv(tmp);
	if (tmp)
		free(tmp);
	return (tmp1);
}

static void	skip_single_quotes(char *line, int *i)
{
	while (line[++(*i)] && line[*i] != '\'')
		;
}

char	*extract_non_env_value(char *line, int *i, int start, int *flag)
{
	while (line && line[*i] && line[*i] != '$')
	{
		if (line[*i] == '"' && *flag == 0)
			*flag = 1;
		else if (line[*i] == '"' && *flag == 1)
			*flag = 0;
		else if (line[*i] == '\'' && *flag == 0)
			skip_single_quotes(line, i);
		(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:53:38 by sasano            #+#    #+#             */
/*   Updated: 2024/03/29 18:49:10 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_error = false;

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}

// void	err_todo(const char *msg)
// {
// 	dprintf(STDERR_FILENO, "minishell: %s\n", msg);
// 	exit(255);
// }

void	tokenize_error(const char *location, char *line)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "Syntax Error: %s\n", location);
	while (*line)
		line++;
}
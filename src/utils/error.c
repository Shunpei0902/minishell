/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:53:38 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 18:56:58 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_syntax_error = false;

void	fatal_error(const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Fatal Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(status);
}

void	error_message(const char *location, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_message3(const char *location, const char *msg, const char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

void	tokenize_error(const char *location, char **line)
{
	g_syntax_error = true;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Syntax Error: ", STDERR_FILENO);
	ft_putendl_fd(location, STDERR_FILENO);
	while (**line && **line != '\n')
		(*line)++;
}

void	parse_error(const char *location, t_token **tokens)
{
	g_syntax_error = true;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Parse Error: ", STDERR_FILENO);
	ft_putendl_fd(location, STDERR_FILENO);
	while (*tokens != NULL && (*tokens)->type != TOKEN_EOF)
		*tokens = (*tokens)->next;
}

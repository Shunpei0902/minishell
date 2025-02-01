/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:34:36 by niida             #+#    #+#             */
/*   Updated: 2025/02/02 03:50:39 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"

bool	is_builtin(t_node *node)
{
	char	*cmd;
	int		i;

	static char *builtin[BUILT_IN_COUNT] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	if (node == NULL || node->args == NULL || node->args->value == NULL
		|| node->args->value[0] == '\0')
		return (false);
	cmd = node->args->value;
	i = 0;
	while (i < BUILT_IN_COUNT)
	{
		if (ft_strcmp(cmd, builtin[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_node *node)
{
	int		status;
	char	**argv;

	redirect(node->redirects);
	argv = tokens_to_argv(node->args);
	status = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
		status = b_echo(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = b_cd(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = b_pwd(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = b_export(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = b_unset(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = b_env(argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		status = b_exit(argv);
	reset_redirect(node->redirects);
	free(argv);
	return (status);
}

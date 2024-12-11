/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:34:36 by niida             #+#    #+#             */
/*   Updated: 2024/12/09 17:44:45 by naokiiida        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "minishell.h"

typedef int	(*t_function)(char **);

int	is_builtin(char *cmd)
{
	int			i;
	static char	*builtin[BUILT_IN_COUNT] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	i = BUILT_IN_COUNT;
	while (--i >= 0)
		if (ft_strncmp(cmd, builtin[i], ft_strlen(builtin[i])) == 0)
			return (i);
	return (-1);
}

int	exec_builtin(int i, char **cmd)
{
	static t_function	run[BUILT_IN_COUNT] = {
		b_echo,
		b_cd,
		b_pwd,
		b_export,
		b_unset,
		b_env,
		b_exit,
	};

	run[i](cmd);
	return (0);
}

// int	main(void)
// {
// 	char *commands[][4] = {
// 	{"echo", "-n", "is here", NULL},
// 	{"echo", "word=TEST", "is here", NULL},
// 	{"echo", "\"word=TEST\"", "is here", NULL},
// 	{"echo", "'word=TEST'", "is here", NULL},
// 	{"cd", NULL},
// 	{"pwd", NULL},
// 	{"cd", "/usr/local/bin", "asdfasdf", NULL},
// 	{"pwd", NULL},
// 	{"cd", "..", NULL},
// 	{"pwd", NULL},
// 	{"export", NULL},
// 	{"unset", NULL},
// 	{"env", NULL},
// 	{"exit", NULL},
// 	{"exit", "1", NULL},
// 	{NULL}
// 	};
// 	int i;
// 	int j;
// 	int k;

// 	printf("run...\n");
// 	for (i = 0; commands[i][0] != NULL; i++)
// 	{
// 		printf("\nTesting command: ");
// 		for (k = 0; commands[i][k] != NULL; k++)
// 		{
// 			printf("%s ", commands[i][k]);
// 		}
// 		j = is_builtin(commands[i][0]);
// 		if (j >= 0)
// 			exec_builtin(j, commands[i]);
// 		else
// 			printf("%s not found\n", commands[i][0]);
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:49:23 by niida             #+#    #+#             */
/*   Updated: 2024/04/13 17:00:51 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char g_pwd[PATH_MAX];
//TODO: CDPATH
//TODO: assert("cd -", "cd $OLDPWD")
/**
BASH(1)
cd [-L|-P] [dir]
    Change the current directory to dir.  The variable HOME is the default dir.  The variable CDPATH defines the search path for the directory containing dir.  Alternative
    directory names in CDPATH are separated by a colon (:).  A null directory name in CDPATH is the same as the current directory, i.e., ``.''.  If dir begins with a slash
    (/), then CDPATH is not used. The -P option says to use the physical directory structure instead of following symbolic links (see also the -P option to the set builtin
    command); the -L option forces symbolic links to be followed.  An argument of - is equivalent to $OLDPWD.  If a non-empty directory name from CDPATH is used, or if -
    is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output.  The return value
    is true if the directory was successfully changed; false otherwise.
*/
void b_cd(char **av)
{
	int		status;
	char	*path;
	char	*oldpath;

	path = *++av;
	oldpath = getenv("PWD");

	if (!path || *path == '~')
		path = getenv("HOME");
	status = chdir(path);
	if (status < 0)
		err_exit("cd", " no such file or directory", 1);
	ft_setenv("PWD", path, 1);
	ft_setenv("OLDPWD", oldpath, 1);
	exit(0);
}

void b_pwd(char **av)
{
	(void)av;
	if (!getcwd(g_pwd, PATH_MAX))
		err_exit("pwd", "getcwd", 1);
	ft_setenv("PWD", g_pwd, 1);
	write(1, g_pwd, ft_strlen(g_pwd));
	write(1, "\n", 1);
	exit(0);
}

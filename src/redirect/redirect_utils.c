/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:06:54 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 10:09:39 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_delimiter(char **delimiter, int *flag)
{
	int		i;
	char	*tmp;

	i = -1;
	*flag = 0;
	tmp = *delimiter;
	while (tmp[++i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			*flag = 1;
			break ;
		}
	}
	i = 0;
	*delimiter = quote_expand(*delimiter, &i);
	free(tmp);
}

void	expand_heredoc(char **line, int flag)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!*line || **line == '\0' || **line == '\n')
		return ;
	if (!flag)
	{
		tmp = *line;
		*line = param_expand(*line, &i, 0);
		free(tmp);
	}
}

bool	should_stop_heredoc(char *line, char *delimiter)
{
	return (!line || (ft_strncmp(line, delimiter,
				ft_strlen(line)) == 0 && *line != '\0')
		|| (*line == '\n' && !delimiter)
		|| g_readline_interrupted);
}

void	process_heredoc(int fd[2], char *delimiter, int flag)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (should_stop_heredoc(line, delimiter))
		{
			free(line);
			break ;
		}
		expand_heredoc(&line, flag);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
}

int	read_heredoc(char *delimiter)
{
	int	fd[2];
	int	flag;

	if (pipe(fd) < 0)
		fatal_error("pipe");
	expand_delimiter(&delimiter, &flag);
	g_readline_interrupted = false;
	process_heredoc(fd, delimiter, flag);
	if (g_readline_interrupted)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

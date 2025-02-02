/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:24:28 by sasano            #+#    #+#             */
/*   Updated: 2025/02/02 16:43:34 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_value(char *line, int *i, int *flag)
{
	int		start;
	char	*value;

	value = get_env(line, i, &start);
	if (!value && line[start] && line[start] != '$')
		value = extract_non_env_value(line, i, start, flag);
	return (value);
}

char	*param_expand(char *line, int *i, int flag)
{
	char	*value;
	char	*tmp;
	char	*tmp1;
	int		start;

	if (!line || !line[*i])
		return (NULL);
	start = *i;
	value = NULL;
	tmp = NULL;
	value = get_expanded_value(line, i, &flag);
	tmp = param_expand(line, i, flag);
	tmp1 = xstrjoin(value, tmp);
	if (line[start] != '$' || (line[start] == '$' && (line[start + 1] == '$'
				|| line[start + 1] == '\0' || line[start + 1] == '?')))
		free(value);
	if (tmp)
		free(tmp);
	return (tmp1);
}

static void	expand_parm_tok(t_token *tokens)
{
	int		i;
	char	*tmp;
	t_token	*tmp_token;

	tmp_token = 0;
	while (tokens && g_syntax_error == false)
	{
		if (tokens->type == TOKEN_WORD && (!tmp_token
				|| tmp_token->type != TOKEN_REDIR_HEREDOC))
		{
			i = 0;
			tmp = tokens->value;
			tokens->value = param_expand(tokens->value, &i, 0);
			free(tmp);
		}
		tmp_token = tokens;
		tokens = tokens->next;
	}
}

void	expand_parameter(t_node *node)
{
	if (!node || node->type == NODE_REDIR_HEREDOC)
		return ;
	expand_parm_tok(node->args);
	expand_parm_tok(node->filename);
	expand_parameter(node->redirects);
	expand_parameter(node->next);
}

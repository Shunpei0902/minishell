/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:00:42 by sasano            #+#    #+#             */
/*   Updated: 2024/12/13 12:28:51 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

// GNU readline uses FILE data type, part of stdio.h
# include <stdio.h>
// GNU readline
# include <readline/history.h>
# include <readline/readline.h>
// signal handling
# include <signal.h>

extern bool						g_syntax_error;
extern int						g_last_status;
extern bool						g_readline_interrupted;
extern volatile sig_atomic_t	g_sig;
extern char						**environ;

// トークンの種類
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}								t_token_type;

// トークンの構造体
// typedef struct s_token	t_token;
typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

// ノードの種類
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_REDIR_HEREDOC
}								t_node_type;

// ノードの構造体
// typedef struct s_node	t_node;
typedef struct s_node
{
	t_node_type					type;
	struct s_node				*next;
	t_token						*args;
	struct s_node				*redirects;
	t_token						*filename;
	int							filefd;
	int							targetfd;
	int							stashed_targetfd;
	int							inpipe[2];
	int							outpipe[2];
}								t_node;

void							set_signal(void);
void							reset_signal(void);
char							check_isalpha_isunder(char str);
void							fatal_error(const char *msg) __attribute__((noreturn));
void							err_exit(const char *location, const char *msg,
									int status);
void							tokenize_error(const char *location,
									char **line);
void							parse_error(const char *location,
									t_token **tokens);
void							free_tokens(t_token *tokens);
void							free_argv(char **argv);
void							free_node(t_node *node);
bool							check_quote(char *line, int i);
char							*get_word(char *line, int *i);
t_token							*tokenize(char *line);
void							expand(t_token *tokens);
char							*param_expand(char *line, int *i, int flag);
char							*quote_expand(char *line, int *i);
t_node							*parse(t_token *tokens);
void							open_redir_file(t_node *node);
void							redirect(t_node *node);
void							reset_redirect(t_node *node);
int								read_heredoc(char *delimiter);
void							expand_heredoc(char **line, int flag);
void							prepare_pipe(t_node *node);
void							pipe_parent(t_node *node);
void							pipe_child(t_node *node);
bool							check_pipe(t_token *token);
t_node_type						check_redirect(t_token *token);
char							**tokens_to_argv(t_token *tokens);
char							*search_path(const char *filename);
void							validate_path(const char *path,
									const char *filename);
pid_t							exec_pipe(t_node *node);
char							*get_env(char *line, int *i, int *start);
char							check_isalpha_isunder(char str);
void							expand_delimiter(char **delimiter, int *flag);
void							add_token(t_token **head, t_token *current);
char							validate_quote(char *line, int *i, int *start,
									int *end);
enum e_token_type				check_token_type(char *line, int i);
bool							check_symbol(char *line, int i);
bool							check_quote(char *line, int i);
void							skip_single_quotes(char *line, int *i);
char							*extract_non_env_value(char *line, int *i,
									int start, int *flag);
char							*get_expanded_value(char *line, int *i,
									int *flag);
int								read_heredoc(char *delimiter);
int								b_echo(char **av);
int								b_cd(char **av);
// int	b_pwd(void);
int								b_pwd(char **av);
int								b_export(char **av);
int								b_unset(char **av);
// int	b_env(void);
int								b_env(char **av);
int								b_exit(char **av);

typedef int						(*t_function)(char **);
int								is_builtin(char *cmd);
int								exec_builtin(int i, char **cmd);
void							update_environ(void);
int								exec_builtin_command(int builtin_id, char **argv, t_node *node);

#endif

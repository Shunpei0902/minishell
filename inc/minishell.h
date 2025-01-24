/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:00:42 by sasano            #+#    #+#             */
/*   Updated: 2025/01/24 18:00:27 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "hashmap.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

extern bool						g_syntax_error;
extern int						g_last_status;
extern bool						g_readline_interrupted;
extern volatile sig_atomic_t	g_sig;
extern t_bucket					*g_envmap[TABLESIZE];
extern char						**environ;

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

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_REDIR_HEREDOC
}								t_node_type;

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

// main

// error
void							err_exit(const char *location, const char *msg,
									int status);
void							tokenize_error(const char *location,
									char **line);
void							parse_error(const char *location,
									t_token **tokens);
void							fatal_error(const char *msg);
void							error_message(const char *location,
									const char *msg);
void							error_message3(const char *location,
									const char *msg, const char *arg);
// free
void							free_tokens(t_token *tokens);
void							free_argv(char **argv);
void							free_node(t_node *node);

void							set_signal(void);
void							reset_signal(void);
bool							check_quote(char *line, int i);
char							*get_word(char *line, int *i);
t_token							*tokenize(char *line);
t_node							*parse(t_token *tokens);
void							open_redir_file(t_node *node);
void							redirect(t_node *node);
void							reset_redirect(t_node *node);
int								read_heredoc(char *delimiter);
void							expand_heredoc(char **line, int flag);

// expand
void							expand(t_node *node);
void							expand_parameter(t_node *node);
void							expand_word_splitting(t_node *node);
void							expand_quote_removal(t_node *node);
char							*param_expand(char *line, int *i, int flag);
char							*quote_expand(char *line, int *i);
char							*extract_non_env_value(char *line, int *i,
									int start, int *flag);
char							*get_env(char *line, int *i, int *start);

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
void							expand_delimiter(char **delimiter, int *flag);
void							add_token(t_token **head, t_token *current);
char							validate_quote(char *line, int *i, int *start,
									int *end);
enum e_token_type				check_token_type(char *line, int i);
bool							check_symbol(char *line, int i);
bool							check_quote(char *line, int i);
int								read_heredoc(char *delimiter);

// buildin
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
bool							is_builtin(t_node *node);
int								exec_builtin(t_node *node);
;

// xlib
void							*xcalloc(size_t count, size_t size);
void							*xmalloc(size_t size);
char							*xstrdup(const char *s);
char							*xstrcdup(const char *s, int c);
char							*xstrjoin(char *s1, char *s2);
char							*xgetenv(const char *name);

// utils
int								ft_strcmp(const char *str1, const char *str2);
#endif

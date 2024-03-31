#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
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
}					t_token_type;

// トークンの構造体
// typedef struct s_token	t_token;
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

//ノードの種類
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_REDIR_HEREDOC
}					t_node_type;

// ノードの構造体
// typedef struct s_node	t_node;
typedef struct s_node
{
	t_node_type		type;
	struct s_node	*next;
	t_token			*args;
	struct s_node	*redirects;
	t_token			*filename;
	int				filefd;
	int				targetfd;
	int				stashed_targetfd;
}					t_node;

extern bool			g_syntax_error;

void				fatal_error(const char *msg) __attribute__((noreturn));
void				err_exit(const char *location, const char *msg, int status);
void				tokenize_error(const char *location, char *line);
void				parse_error(const char *location, t_token **tokens);
void				free_tokens(t_token *tokens);
void				free_argv(char **argv);
void				free_node(t_node *node);
t_token				*tokenize(char *line);
t_node				*parse(t_token *tokens);
void				open_redir_file(t_node *node);
void				redirect(t_node *node);
void				reset_redirect(t_node *node);
int					read_heredoc(const char *delimiter);

#endif

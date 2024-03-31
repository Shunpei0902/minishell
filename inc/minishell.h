#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// GNU readline uses FILE data type, part of stdio.h
# include <stdio.h>
// GNU readline
# include <readline/history.h>
# include <readline/readline.h>

# define NOT_QUOTE 1

// トークンの種類
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_SEMICOLON,
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
}					t_node_type;

// ノードの構造体
// typedef struct s_node	t_node;
typedef struct s_node
{
	t_token			*args;
	t_node_type		type;
	struct s_node	*next;
}					t_node;

extern bool			syntax_error;

void				fatal_error(const char *msg) __attribute__((noreturn));
void				err_exit(const char *location, const char *msg, int status);
void				tokenize_error(const char *location, char *line);
void				free_tokens(t_token *tokens);
void				free_argv(char **argv);
t_token				*tokenize(char *line);
t_node				*parse(t_token *tokens);

#endif

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

// GNU readline uses FILE data type, part of stdio.h
# include <stdio.h>
// GNU readline
# include <readline/history.h>
# include <readline/readline.h>

// トークンの種類
enum					e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_SEMICOLON,
	TOKEN_EOF
}						t_token_type;

// トークンの構造体
typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}						t_token;

bool					syntax_error = false;

void					fatal_error(const char *msg);
t_token					*tokenize(char *line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:39:49 by sasano            #+#    #+#             */
/*   Updated: 2024/03/29 09:21:01 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // あなたのヘッダーファイルのパスに置き換えてください
#include <stdio.h>

// トークンタイプを文字列で返す関数
const char	*token_type_to_string(enum e_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return ("WORD");
	case TOKEN_PIPE:
		return ("PIPE");
	case TOKEN_REDIR_IN:
		return ("REDIR_IN");
	case TOKEN_REDIR_OUT:
		return ("REDIR_OUT");
	case TOKEN_REDIR_APPEND:
		return ("REDIR_APPEND");
	case TOKEN_SEMICOLON:
		return ("SEMICOLON");
	case TOKEN_EOF:
		return ("EOF");
	default:
		return ("UNKNOWN");
	}
}

// トークンリストを表示する関数
void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		printf("Type: %s, Value: %s\n", token_type_to_string(current->type),
			current->value ? current->value : "NULL");
		current = current->next;
	}
}

// テスト関数
void	test_tokenize(char *input)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*next;

	printf("Testing tokenize for input: %s\n", input);
	tokens = tokenize(input);
	print_tokens(tokens);
	// トークンリストのメモリを解放する
	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value); // strdup または類似の関数を使用している場合
		free(current);
		current = next;
	}
}

// int	main(void)
// {
// 	test_tokenize("ls -l | grep 'txt' > output.txt");
// 	test_tokenize("echo \"Hello, world\" && echo Goodbye");
// 	test_tokenize("echo \"Hello,   world\" && echo >>  <<Goodbye");
// 	// 他のテストケースを追加
// 	return (0);
// }

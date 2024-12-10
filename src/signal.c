/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:20:46 by sasano            #+#    #+#             */
/*   Updated: 2024/11/21 15:57:22 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_status = 1;
}

void	set_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// SIGINT の設定
	sa_int.sa_handler = sigint_handler; // カスタムハンドラ
	sigemptyset(&sa_int.sa_mask);       // 他のシグナルをブロックしない
	sa_int.sa_flags = SA_RESTART;       // システムコールを再始動
	// SIGQUIT の設定
	sa_quit.sa_handler = SIG_IGN;  // 無視する
	sigemptyset(&sa_quit.sa_mask); // 他のシグナルをブロックしない
	sa_quit.sa_flags = 0;          // 特別なフラグはなし
	// sigaction を適用
	if (sigaction(SIGINT, &sa_int, NULL) == -1 || sigaction(SIGQUIT, &sa_quit,
															NULL)) // ハンドラを設定
		fatal_error("sigaction");
}

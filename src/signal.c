/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:20:46 by sasano            #+#    #+#             */
/*   Updated: 2024/12/11 17:35:21 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig = 0;

void	sigint_handler(int signo)
{
	sig = signo;
	// (void)signo;
	// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// g_last_status = 1;
}

int	check_state(void)
{
	if (sig == 0)
		return (0);
	else if (sig == SIGINT)
	{
		sig = 0;
		readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	set_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	extern int			_rl_echo_control_chars;

	_rl_echo_control_chars = 0; // Ctrl+Cの制御文字を画面に表示しない
	rl_outstream = stderr;      //エラーメッセージをstderrに出力
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
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

void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}

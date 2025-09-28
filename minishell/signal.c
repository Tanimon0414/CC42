/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:08 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:09:52 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals_interactive(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_non_interactive(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

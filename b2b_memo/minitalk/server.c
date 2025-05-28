/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:12:36 by kishigam          #+#    #+#             */
/*   Updated: 2022/08/30 00:52:01 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "Libft/libft.h"

static void	is_kill_caused_error(int num)
{
	if (num == -1)
		exit(1);
}

static void	action(int sig, siginfo_t *info, void *ctx)
{
	static int				i = 0;
	static unsigned char	c = 0;
	pid_t					client_pid;

	client_pid = 0;
	(void)ctx;
	if (!client_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			is_kill_caused_error(kill(client_pid, SIGUSR2));
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		is_kill_caused_error(kill(client_pid, SIGUSR1));
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}

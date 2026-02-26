/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:03:45 by atanimot          #+#    #+#             */
/*   Updated: 2025/08/02 14:10:05 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	exit_with_numeric_error(const char *arg)
{
	write(1, "exit\n", 5);
	put_error_str("exit: ", (char *)arg, ": numeric argument required\n");
	exit(2);
}

static void	exit_with_too_many_args_error(void)
{
	write(STDERR_FILENO, "exit\nexit: too many arguments\n",
		ft_strlen("exit\nexit: too many arguments\n"));
}

int	non_number(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '+' || c[i] == '-')
		i++;
	if (c[i] == '\0')
		return (1);
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	execute_exit(char **args, t_shell *shell)
{
	int			arg_count;
	long long	status;

	arg_count = count_args(args);
	if (arg_count == 1)
	{
		printf("exit\n");
		exit(shell->last_status);
	}
	if (non_number(args[1]))
		exit_with_numeric_error(args[1]);
	if (arg_count > 2)
	{
		exit_with_too_many_args_error();
		shell->last_status = 1;
		return ;
	}
	status = ft_atoll(args[1]);
	exit(status % 256);
}

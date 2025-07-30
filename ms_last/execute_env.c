/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:08:02 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/27 18:08:16 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (args[1])
	{
		write(STDERR_FILENO, "env: ", ft_strlen("env: "));
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		shell->last_status = 127;
		return ;
	}
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	shell->last_status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:03:45 by atanimot          #+#    #+#             */
/*   Updated: 2025/08/02 14:23:01 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_shell *shell)
{
	if (!ft_strncmp(args[0], "echo", 5))
		execute_echo(args);
	else if (!ft_strncmp(args[0], "cd", 3))
		return (execute_cd(args, shell), shell->last_status);
	else if (!ft_strncmp(args[0], "pwd", 4))
		execute_pwd();
	else if (!ft_strncmp(args[0], "export", 7))
		return (execute_export(args, shell), shell->last_status);
	else if (!ft_strncmp(args[0], "unset", 6))
		return (execute_unset(args, shell), shell->last_status);
	else if (!ft_strncmp(args[0], "env", 4))
		return (execute_env(args, shell), shell->last_status);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (execute_exit(args, shell), shell->last_status);
	return (0);
}

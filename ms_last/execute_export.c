/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:48 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/27 16:46:01 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_export_arg(char *arg, t_shell *shell)
{
	if (ft_strstr(arg, "+="))
		handle_export_append(arg, shell);
	else if (ft_strchr(arg, '='))
		handle_export_assign(arg, shell);
	else
	{
		if (!is_valid_identifier(arg))
			print_identifier_error(arg, &shell->last_status);
	}
}

void	execute_export(char **args, t_shell *shell)
{
	int	i;

	shell->last_status = 0;
	if (!args[1])
	{
		print_exported_vars(shell->envp);
		return ;
	}
	if (args[1][0] == '-')
	{
		write(STDERR_FILENO, "export: invalid option\n", 23);
		shell->last_status = 2;
		return ;
	}
	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], shell);
		i++;
	}
}

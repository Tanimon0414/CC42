/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:48 by atanimot          #+#    #+#             */
/*   Updated: 2025/08/02 14:13:41 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_identifier_error(const char *arg, int *last_status)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	*last_status = 1;
}

void	handle_export_assign(char *arg, t_shell *shell)
{
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	*eq_pos = '\0';
	if (!is_valid_identifier(arg))
		print_identifier_error(arg, &shell->last_status);
	else
		shell->envp = overwrite_env(arg, eq_pos + 1, shell->envp);
	*eq_pos = '=';
}

void	handle_export_append(char *arg, t_shell *shell)
{
	char	*key;
	char	*old_val;
	char	*new_val;
	char	*plus_eq;

	plus_eq = ft_strstr(arg, "+=");
	*plus_eq = '\0';
	key = arg;
	if (!is_valid_identifier(key))
	{
		*plus_eq = '+';
		print_identifier_error(arg, &shell->last_status);
		return ;
	}
	old_val = get_env_value(key, shell->envp);
	if (old_val)
		new_val = ft_strjoin(old_val, plus_eq + 2);
	else
		new_val = ft_strdup(plus_eq + 2);
	if (new_val)
	{
		shell->envp = overwrite_env(key, new_val, shell->envp);
		free(new_val);
	}
	*plus_eq = '+';
}

static void	process_export_arg(char *arg, t_shell *shell)
{
	if (ft_strstr(arg, "+="))
		handle_export_append(arg, shell);
	else if (ft_strchr(arg, '='))
		handle_export_assign(arg, shell);
	else
		handle_export_no_value(arg, shell);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:21:51 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/28 10:42:43 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**prepare_executable_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] && is_empty_or_whitespace(args[i]))
	{
		i++;
	}
	if (!args[i])
	{
		exit(0);
	}
	return (&args[i]);
}

static void	handle_special_dot_commands(const char *cmd)
{
	if (ft_strcmp(cmd, ".") == 0)
	{
		put_error_str(".: filename argument required\n", NULL, NULL);
		exit(2);
	}
	if (ft_strcmp(cmd, "..") == 0)
	{
		put_error_str("..: command not found\n", NULL, NULL);
		exit(127);
	}
	if (ft_strcmp(cmd, "~") == 0)
	{
		put_error_str("~: Is a directory\n", NULL, NULL);
		exit(126);
	}
}

static void	execute_absolute_path(const char *cmd, char **args, t_shell *shell)
{
	struct stat	sb;

	if (stat(cmd, &sb) == -1)
	{
		put_error_str((char *)cmd, ": ", strerror(errno));
		exit(127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		put_error_str((char *)cmd, ": Is a directory\n", NULL);
		exit(126);
	}
	if (access(cmd, X_OK) == -1)
	{
		put_error_str((char *)cmd, ": ", strerror(errno));
		exit(126);
	}
	execve(cmd, args, shell->envp);
	perror(cmd);
	exit(126);
}

static void	execute_from_path(const char *cmd, char **args, t_shell *shell)
{
	char	*path;

	path = find_path((char *)cmd, shell->envp);
	if (!path)
	{
		put_error_str((char *)cmd, ": command not found\n", NULL);
		exit(127);
	}
	execve(path, args, shell->envp);
	perror(path);
	free(path);
	exit(126);
}

void	execute_cmd(t_cmd *cmd_node, t_shell *shell)
{
	char	**args;
	char	*cmd;

	args = prepare_executable_args(cmd_node->args);
	cmd = args[0];
	handle_special_dot_commands(cmd);
	if (is_builtin(cmd))
	{
		shell->last_status = execute_builtin(args, shell);
		exit(shell->last_status);
	}
	if (ft_strchr(cmd, '/'))
	{
		execute_absolute_path(cmd, args, shell);
	}
	else
	{
		execute_from_path(cmd, args, shell);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:11:59 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/28 18:25:53 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_cd_args(char **args, int *last_status)
{
	if (args[1])
	{
		if (args[2])
		{
			write(STDERR_FILENO, "cd: too many arguments\n", 23);
			*last_status = 1;
			return (1);
		}
		if (args[1][0] == '-' && args[1][1] != '\0' && ft_strcmp(args[1],
				"-") != 0 && ft_strcmp(args[1], "--") != 0)
		{
			write(STDERR_FILENO, "cd: invalid option\n", 19);
			*last_status = 2;
			return (1);
		}
	}
	return (0);
}

static char	*get_old_pwd(char **envp)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(get_env_value("PWD", envp)));
}

static void	update_cd_env(t_shell *shell, char *oldpwd)
{
	char	cwd[1024];

	shell->envp = overwrite_env("OLDPWD", oldpwd, shell->envp);
	if (getcwd(cwd, sizeof(cwd)))
		shell->envp = overwrite_env("PWD", cwd, shell->envp);
}

static void	perform_cd(t_shell *shell, char *target, char *oldpwd, int n_free)
{
	if (!target)
	{
		shell->last_status = 1;
		return ;
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		shell->last_status = 1;
	}
	else
	{
		update_cd_env(shell, oldpwd);
		shell->last_status = 0;
	}
	if (n_free)
		free(target);
}

void	execute_cd(char **args, t_shell *shell)
{
	char	*target;
	char	*oldpwd;
	int		needs_free;

	if (validate_cd_args(args, &shell->last_status))
		return ;
	oldpwd = get_old_pwd(shell->envp);
	if (!oldpwd)
	{
		perror("cd");
		shell->last_status = 1;
		return ;
	}
	target = get_cd_target(args, shell->envp, &needs_free);
	perform_cd(shell, target, oldpwd, needs_free);
	free(oldpwd);
}

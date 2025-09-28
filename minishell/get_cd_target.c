/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_target.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:20:24 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/28 17:14:30 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_home(char **envp)
{
	char	*target;

	target = get_env_value("HOME", envp);
	if (!target)
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
	return (target);
}

static char	*get_target_home_suffix(char *arg, char **envp)
{
	char	*home;
	char	*target;

	home = get_env_value("HOME", envp);
	if (!home)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
		return (NULL);
	}
	target = ft_strjoin(home, arg + 1);
	return (target);
}

static char	*get_target_oldpwd(char **envp)
{
	char	*target;

	target = get_env_value("OLDPWD", envp);
	if (target)
		printf("%s\n", target);
	else
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
	return (target);
}

char	*get_cd_target(char **args, char **envp, int *needs_free)
{
	*needs_free = 0;
	if (!args[1] || ft_strcmp(args[1], "~") == 0 || ft_strcmp(args[1],
			"--") == 0)
		return (get_target_home(envp));
	if (args[1][0] == '~' && args[1][1] == '/')
	{
		*needs_free = 1;
		return (get_target_home_suffix(args[1], envp));
	}
	if (ft_strcmp(args[1], "-") == 0)
		return (get_target_oldpwd(envp));
	return (args[1]);
}

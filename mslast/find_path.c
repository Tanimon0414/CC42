/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:07 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/28 11:12:01 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*full;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strcpy(full, path);
	ft_strcat(full, "/");
	ft_strcat(full, cmd);
	return (full);
}

static char	*find_full_path(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*path_env;
	char	*full_path;

	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			return (free(paths), full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	return (free(paths), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		return (find_full_path(cmd, envp, i));
	else
	{
		if (access(cmd, X_OK) == 0)
		{
			full_path = join_path_cmd(".", cmd);
			return (full_path);
		}
	}
	return (NULL);
}

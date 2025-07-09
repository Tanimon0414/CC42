/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 08:18:52 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/09 17:41:45 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

void	exit_with_error(char *message, t_all *all)
{
	perror(message);
	if (all)
	{
		if (all->input_fd > 2)
			close(all->input_fd);
		if (all->output_fd > 2)
			close(all->output_fd);
		if (all->pipefd[0] > 2)
			close(all->pipefd[0]);
		if (all->pipefd[1] > 2)
			close(all->pipefd[1]);
		free(all);
	}
	exit(1);
}

void	free_char_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

static char	*search_in_paths(char *cmd, char **all_paths)
{
	char	*path_part;
	char	*full_path;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		if (!path_part)
			return (NULL);
		full_path = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path_env;
	char	*executable_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = find_path_env(envp);
	if (!path_env)
		return (NULL);
	all_paths = ft_split(path_env, ':');
	if (!all_paths)
		return (NULL);
	executable_path = search_in_paths(cmd, all_paths);
	free_char_array(all_paths);
	return (executable_path);
}

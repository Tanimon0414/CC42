/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:03:45 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/27 19:05:31 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *name, char **envp)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*create_env_entry(const char *key, const char *value)
{
	size_t	key_len;
	size_t	val_len;
	char	*entry;

	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	entry = malloc(key_len + val_len + 2);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, key, key_len);
	entry[key_len] = '=';
	ft_memcpy(entry + key_len + 1, value, val_len);
	entry[key_len + 1 + val_len] = '\0';
	return (entry);
}

static char	**add_new_env(char **envp, char *new_entry)
{
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
	{
		free(new_entry);
		return (envp);
	}
	count = 0;
	while (envp[count])
	{
		new_envp[count] = envp[count];
		count++;
	}
	free(envp);
	new_envp[count] = new_entry;
	new_envp[count + 1] = NULL;
	return (new_envp);
}

char	**overwrite_env(const char *key, const char *value, char **envp)
{
	char	*new_entry;
	size_t	key_len;
	int		i;

	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (envp);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (envp);
		}
		i++;
	}
	return (add_new_env(envp, new_entry));
}

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
		execute_exit(args);
	return (0);
}

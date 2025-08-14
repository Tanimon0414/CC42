/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:22:58 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:22:59 by kkuramot         ###   ########.fr       */
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

static char	**find_env_var(const char *key, char **envp)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
		{
			if (envp[i][key_len] == '=' || envp[i][key_len] == '\0')
				return (&envp[i]);
		}
		i++;
	}
	return (NULL);
}

char	*create_env_entry(const char *key, const char *value)
{
	char	*entry;
	char	*tmp;

	if (value == NULL)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
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
	char	**found_ptr;
	char	*new_entry;

	found_ptr = find_env_var(key, envp);
	if (value == NULL && found_ptr != NULL)
		return (envp);
	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (envp);
	if (found_ptr != NULL)
	{
		free(*found_ptr);
		*found_ptr = new_entry;
		return (envp);
	}
	return (add_new_env(envp, new_entry));
}

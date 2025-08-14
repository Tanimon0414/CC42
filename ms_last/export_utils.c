/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by atanimot          #+#    #+#             */
/*   Updated: 2025/08/02 14:20:42 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || str[0] == '\0' || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_export_no_value(char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
		print_identifier_error(arg, &shell->last_status);
	else
		shell->envp = overwrite_env(arg, NULL, shell->envp);
}

static char	**create_sorted_env_copy(char **envp, int count, int i)
{
	char	**new_array;
	char	*tmp;
	int		j;

	new_array = malloc(sizeof(char *) * (count + 1));
	if (!new_array)
		return (NULL);
	while (++i < count)
		new_array[i] = envp[i];
	new_array[count] = NULL;
	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_strcmp(new_array[j], new_array[j + 1]) > 0)
			{
				tmp = new_array[j];
				new_array[j] = new_array[j + 1];
				new_array[j + 1] = tmp;
			}
		}
	}
	return (new_array);
}

static void	print_formatted_vars(char **sorted_envp)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (sorted_envp[i])
	{
		eq_pos = ft_strchr(sorted_envp[i], '=');
		if (eq_pos)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq_pos - sorted_envp[i]),
				sorted_envp[i], eq_pos + 1);
		else
			printf("declare -x %s\n", sorted_envp[i]);
		i++;
	}
}

void	print_exported_vars(char **envp)
{
	char	**sorted_envp;
	int		count;

	count = 0;
	while (envp[count])
		count++;
	if (count == 0)
		return ;
	sorted_envp = create_sorted_env_copy(envp, count, -1);
	if (!sorted_envp)
		return ;
	print_formatted_vars(sorted_envp);
	free(sorted_envp);
}

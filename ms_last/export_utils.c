/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/27 16:50:33 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_identifier_error(const char *arg, int *last_status)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	*last_status = 1;
}

void	print_exported_vars(char **envp)
{
	char	*eq_pos;
	int		i;

	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq_pos - envp[i]), envp[i],
				eq_pos + 1);
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
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

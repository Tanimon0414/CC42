/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:04:28 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/28 17:12:30 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_unset_option_error(const char *arg, int *last_status)
{
	if (arg[0] != '-')
		return (0);
	write(STDERR_FILENO, "unset: `", ft_strlen("unset: `"));
	write(STDERR_FILENO, &arg[0], 1);
	write(STDERR_FILENO, &arg[1], 1);
	write(STDERR_FILENO, "': invalid option\n",
		ft_strlen("': invalid option\n"));
	*last_status = 2;
	return (1);
}

static void	find_and_remove_env_var(const char *arg, t_shell *shell)
{
	int		env_idx;
	size_t	key_len;
	char	**shift_ptr;

	env_idx = 0;
	key_len = ft_strlen(arg);
	while (shell->envp && (shell->envp)[env_idx])
	{
		if (ft_strncmp((shell->envp)[env_idx], arg, key_len) == 0
			&& (shell->envp)[env_idx][key_len] == '=')
		{
			free((shell->envp)[env_idx]);
			shift_ptr = &((shell->envp)[env_idx]);
			while (*shift_ptr)
			{
				*shift_ptr = *(shift_ptr + 1);
				shift_ptr++;
			}
			return ;
		}
		env_idx++;
	}
}

void	execute_unset(char **args, t_shell *shell)
{
	int	i;

	shell->last_status = 0;
	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (handle_unset_option_error(args[i], &shell->last_status))
			return ;
		find_and_remove_env_var(args[i], shell);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:27:43 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/27 16:28:02 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(void)
{
	char	cwd[1024];
	char	*fallback_pwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
	}
	else
	{
		fallback_pwd = getenv("PWD");
		if (fallback_pwd)
			printf("%s\n", fallback_pwd);
		else
			perror("pwd");
	}
}

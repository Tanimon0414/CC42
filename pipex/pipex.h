/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:33 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/29 18:06:11 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_all
{
	char	**path;
	char	*abpath;
	int		input_fd;
	int		output_fd;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
}			t_all;

char		*find_path_env(char **envp);
void		exit_with_error(char *message, t_all *all);
void		free_char_array(char **arr);
char		*find_command_path(char *cmd, char **envp);
#endif
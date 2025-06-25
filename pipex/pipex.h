/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:33 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/25 18:49:28 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
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
	pid_t	pid;
	int		cmd_num;
}			t_all;

#endif
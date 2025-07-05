/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:43:48 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/05 16:01:42 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(char *cmd_str, t_all *all, char **envp)
{
	char	**path;
	char	*abpath;

	path = ft_split(cmd_str, ' ');
	if (!path)
		exit_with_error("ft_split", all);
	abpath = find_command_path(path[0], envp);
	if (abpath == NULL)
	{
		perror("command not found");
		free_char_array(path);
		free(all);
		exit(127);
	}
	execve(abpath, path, envp);
	perror("execve");
	free_char_array(path);
	free(abpath);
	free(all);
	exit(EXIT_FAILURE);
}

static void	cmd_1(t_all *all, char **argv, char **envp)
{
	all->input_fd = open(argv[1], O_RDONLY);
	if (all->input_fd < 0)
		exit_with_error("open input file", all);
	close(all->pipefd[0]);
	dup2(all->input_fd, STDIN_FILENO);
	close(all->input_fd);
	dup2(all->pipefd[1], STDOUT_FILENO);
	close(all->pipefd[1]);
	execute_command(argv[2], all, envp);
}

static void	cmd_2(t_all *all, char **argv, char **envp)
{
	all->output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (all->output_fd < 0)
		exit_with_error("open output file", all);
	close(all->pipefd[1]);
	dup2(all->pipefd[0], STDIN_FILENO);
	close(all->pipefd[0]);
	dup2(all->output_fd, STDOUT_FILENO);
	close(all->output_fd);
	execute_command(argv[3], all, envp);
}

static int	parent_process(t_all *all)
{
	int	exit_status;

	close(all->pipefd[0]);
	close(all->pipefd[1]);
	waitpid(all->pid1, &(all->status1), 0);
	waitpid(all->pid2, &(all->status2), 0);
	if ((all->status2 & 0xFF) == 0)
		exit_status = (all->status2 >> 8) & 0xFF;
	else
		exit_status = 1;
	free(all);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;

	if (argc != 5)
		return (1);
	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		exit_with_error("malloc", NULL);
	all->input_fd = -1;
	all->output_fd = -1;
	all->pipefd[0] = -1;
	all->pipefd[1] = -1;
	if (pipe(all->pipefd) == -1)
		exit_with_error("pipe", all);
	all->pid1 = fork();
	if (all->pid1 < 0)
		exit_with_error("fork", all);
	if (all->pid1 == 0)
		cmd_1(all, argv, envp);
	all->pid2 = fork();
	if (all->pid2 < 0)
		exit_with_error("fork", all);
	if (all->pid2 == 0)
		cmd_2(all, argv, envp);
	return (parent_process(all));
}

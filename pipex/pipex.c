/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/29 18:08:30 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd_2(t_all *all, char **argv, char **envp)
{
	all->output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (all->output_fd < 0)
		exit_with_error("open output file", all);
	close(all->pipefd[1]);
	dup2(all->pipefd[0], STDIN_FILENO);
	dup2(all->output_fd, STDOUT_FILENO);
	close(all->pipefd[0]);
	close(all->output_fd);
	all->path = ft_split(argv[3], ' ');
	if (!all->path)
		exit_with_error("ft_split", all);
	all->abpath = find_command_path(all->path[0], envp);
	if (all->abpath == NULL)
	{
		perror("command not found");
		free_char_array(all->path);
		exit(127);
	}
	execve(all->abpath, all->path, envp);
	perror("execve in cmd2");
	free_char_array(all->path);
	free(all->abpath);
	free(all);
	exit(1);
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
	all->path = ft_split(argv[2], ' ');
	if (!all->path)
		exit_with_error("ft_split", all);
	all->abpath = find_command_path(all->path[0], envp);
	if (all->abpath == NULL)
	{
		perror("command not found");
		free_char_array(all->path);
		exit(127);
	}
	execve(all->abpath, all->path, envp);
	perror("execve in cmd1");
	free_char_array(all->path);
	free(all->abpath);
	free(all);
	exit(1);
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
	if (pipe(all->pipefd) == -1)
		exit_with_error("pipe", all);
	all->pid1 = fork();
	if (all->pid1 == 0)
		cmd_1(all, argv, envp);
	all->pid2 = fork();
	if (all->pid2 == 0)
		cmd_2(all, argv, envp);
	close(all->pipefd[0]);
	close(all->pipefd[1]);
	waitpid(all->pid1, &(all->status1), 0);
	waitpid(all->pid2, &(all->status2), 0);
	free(all);
	if (WIFEXITED(all->status2))
		return (WEXITSTATUS(all->status2));
	return (1);
}

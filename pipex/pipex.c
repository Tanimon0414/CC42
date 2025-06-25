/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/25 19:57:55 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_2(t_all *all, char **argv, char **envp)
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
	all->abpath = ft_strjoin("/bin/", all->path[0]);
	execve(all->abpath, all->path, envp);
	perror("execve");
	free(all); // 念のため確保したメモリを解放
				// ft_splitやft_strjoinで確保したメモリも解放するとさらに丁寧
	exit(1);
}

void	cmd_1(t_all *all, char **argv, char **envp)
{
	close(all->pipefd[0]);
	dup2(all->input_fd, STDIN_FILENO);
	close(all->input_fd);
	dup2(all->pipefd[1], STDOUT_FILENO);
	close(all->pipefd[1]);
	all->path = ft_split(argv[2], ' ');
	all->abpath = ft_strjoin("/bin/", all->path[0]);
	execve(all->abpath, all->path, envp);
	perror("execve");
	exit(1);
}

void	exit_with_error(char *message, t_all *all)
{
	perror(message);
	// allがNULLでなく、確保されている場合のみfreeする
	if (all)
	{
		// 開いている可能性のあるfdを念のため閉じる
		if (all->input_fd > 2) // 0,1,2は標準入出力なので避ける
			close(all->input_fd);
		if (all->output_fd > 2)
			close(all->output_fd);
		free(all);
	}
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
	// input_fdやoutput_fdを-1などで初期化しておくと、後のエラー処理で安全
	all->input_fd = -1;
	all->output_fd = -1;
	all->input_fd = open(argv[1], O_RDONLY);
	if (all->input_fd < 0)
		exit_with_error("open input file", all);
	if (pipe(all->pipefd) == -1)
		exit_with_error("pipe", all);
	all->pid = fork();
	if (all->pid == 0)
		cmd_1(all, argv, envp);
	all->pid = fork();
	if (all->pid == 0)
		cmd_2(all, argv, envp);
	close(all->pipefd[0]);
	close(all->pipefd[1]);
	close(all->input_fd); // 親も開いたfdは閉じる
	wait(NULL);
	wait(NULL);
	free(all);
	return (0);
}

// all->path1 = ft_split(argv[2], ' ');
// 	all->path2 = ft_split(argv[3], ' ');
// 	all->abpath1 = ft_strjoin("/bin/", all->path1[0]);
// 	all->abpath2 = ft_strjoin("/bin/", all->path2[0]);
// 	if (pipe(all->pipefd) == -1)
// 		pipe_error();

// void	cmd_loop(t_all *all)
// {
// 	int	prev_pipe_read_end;
// 	int	i;

// 	prev_pipe_read_end = all->input_fd;
// 	i = 0;
// 	while(i < all->cmd_num - 1)
// 	{

// 	}
// }
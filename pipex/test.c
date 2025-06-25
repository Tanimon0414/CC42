/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:06:13 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/24 14:14:29 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	char	*path1;
	char	*path2;
	char	*new_argv1[] = {"ls", "-l", NULL};
	char	*new_argv2[] = {"wc", "-l", NULL};
	pid_t	pid1;
	pid_t	pid2;

	// パイプライン `ls -l | wc -l` を実行するための引数配列
	path1 = "/bin/ls";
	path2 = "/bin/wc";
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	// 1. ls -l を実行する子プロセス1を作成
	pid1 = fork();
	if (pid1 == 0)
	{
		// 子プロセス1 (`ls`)
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		// 【修正点1】execveの正しい呼び出し方
		// 第1引数: フルパス, 第2引数: 引数配列, 第3引数: 環境変数配列
		execve(path1, new_argv1, envp);
		// execveに失敗した場合のフォールバック
		perror("execve ls");
		exit(1);
	}
	// 2. wc -l を実行する子プロセス2を作成
	pid2 = fork();
	if (pid2 == 0)
	{
		// 子プロセス2 (`wc`)
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		// 【修正点2】execlp を execve に書き換え
		// 第1引数: フルパス, 第2引数: 引数配列, 第3引数: 環境変数配列
		execve(path2, new_argv2, envp);
		// execveに失敗した場合のフォールバック
		perror("execve wc");
		exit(1);
	}
	// 親プロセスはパイプを全く使わないので両方閉じる
	close(pipefd[0]);
	close(pipefd[1]);
	// 2つの子プロセスの終了を待つ
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

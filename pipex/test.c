/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:06:13 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/22 19:25:37 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// int	main(void)
// {
// 	const char	*filepath = "test.txt";

// 	// F_OKを使ってファイルの存在をチェック
// 	if (access(filepath, F_OK) == 0)
// 	{
// 		printf("ファイル '%s' は存在します。\n", filepath);
// 	}
// 	else
// 	{
// 		// accessが-1を返した場合、perrorでエラー内容を表示できる
// 		perror("access");
// 		printf("ファイル '%s' は存在しないか、アクセスできません。\n", filepath);
// 	}
// 	return (0);
// }

// main関数の第3引数で環境変数を取得
// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*path;
// 	char	*new_argv[] = {"ls", "-l", "/tmp", NULL};
// 	char	*new_envp[] = {"USER=guest", "HOME=/tmp", NULL};

// 	// 実行したいコマンドのパス
// 	path = "/bin/ls";
// 	// 渡したいコマンドライン引数の配列 (argv)
// 	// argv[0] はコマンド名、argv[1] は "-l"、argv[2] は "/tmp"
// 	// 配列の最後は必ず NULL にする
// 	// 渡したい環境変数の配列 (envp)
// 	// ここでは新しい環境変数を2つ定義
// 	// 配列の最後は必ず NULL にする
// 	printf("これから execve を呼び出します。成功すればこのメッセージは一度しか表示されません。\n");
// 	printf("--- execveによる出力ここから ---\n");
// 	// execve の呼び出し
// 	// execve(path, new_argv, new_envp);
// 	// 現在の環境変数をそのまま引き継ぎたい場合は、mainの第3引数 envp を渡す
// 	execve(path, new_argv, envp);
// 	// !!! 注意 !!!
// 	// execveが成功した場合、以下のコードは絶対に実行されない
// 	perror("execve"); // execveが失敗した場合のみ、ここが実行されエラーが表示される
// 	printf("execve の呼び出しに失敗しました。\n");
// 	return (1); // 失敗したことを示す
// }

int	main(void)
{
	pid_t	pid;

	printf("--- fork()を呼び出す前 (PID: %d) ---\n", getpid());
	// プロセスを複製する
	pid = fork();
	// fork()の戻り値で処理を分岐
	if (pid < 0)
	{
		// fork()に失敗した場合
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		// --- ここは子プロセス ---
		// fork()の戻り値が0だった場合
		printf("これは子プロセスです。\n");
		printf("  - 子プロセスのPID: %d\n", getpid());
		printf("  - 親プロセスのPID: %d\n", getppid());
	}
	else
	{
		// --- ここは親プロセス ---
		// fork()の戻り値が子プロセスのPIDだった場合
		printf("これは親プロセスです。\n");
		printf("  - 親プロセスのPID: %d\n", getpid());
		printf("  - 作成した子プロセスのPID: %d\n", pid);
	}
	// このメッセージは親と子の両方で表示される
	printf("--- fork()呼び出し後 (PID: %d) ---\n", getpid());
	return (0);
}

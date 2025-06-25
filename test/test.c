/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/11 15:41:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/15 21:37:24 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>


int	main(void)
{
	int pipefd[2];
	char buffer[100];
	const char *message = "Hello, Pipe!";

	// パイプを作成
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}

	// 1. pipefd[1] (書き込み口) にメッセージを書き込む
	printf("'%s' というメッセージを pipefd[1] に書き込みます。\n", message);
	write(pipefd[1], message, strlen(message));

	// 2. pipefd[0] (読み込み口) からデータを読み込む
	ssize_t num_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[num_read] = '\0'; // 文字列として扱うためにNULL終端する

	printf("pipefd[0] から読み込んだメッセージ: '%s'\n", buffer);

	// 使い終わったディスクリプタを閉じる
	close(pipefd[0]);
	close(pipefd[1]);

	return (0);
}

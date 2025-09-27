/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/11 11:49:30 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/18 18:28:56 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_loop(int fd, char *rest, char *buffer)
{
	ssize_t bytes;
	char *tmp;

	bytes = 1;
	while (!ft_strchr(rest, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(rest);
			return (NULL);
		}
		buffer[bytes] = '\0';
		tmp = ft_strjoin(rest, buffer);
		free(rest);
		rest = tmp;
	}
	return (rest);
}

static char	*read_until_newline(int fd, char *rest)
{
	char *buffer;
	char *result;

	if (!rest)
		rest = ft_strdup("");
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer || !rest)
	{
		free(buffer);
		free(rest);
		return (NULL);
	}
	result = read_loop(fd, rest, buffer);
	free(buffer);
	return (result);
}

static char	*extract_line(char *rest)
{
	size_t i;
	char *line;

	i = 0;
	if (!rest || !*rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i--)
		line[i] = rest[i];
	return (line);
}

static char	*update_rest(char *rest)
{
	size_t i;
	char *new_rest;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	if (rest[i] == '\0')
	{
		free(rest);
		return (NULL);
	}
	new_rest = ft_strdup(rest + i);
	free(rest);
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char *rest;
	char *line;
	char *new_rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_until_newline(fd, rest);
	if (!rest)
		return (NULL);
	line = extract_line(rest);
	if (!line)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	new_rest = update_rest(rest);
	rest = new_rest;
	return (line);
}

#include <stdio.h>
#include <unistd.h>


int	main(void)
{
	char *line;
	int fd;

	// 標準入力のファイルディスクリプタは0
	fd = 0;

	printf("標準入力を待っています...\n");

	// get_next_lineがNULLを返すまでループ
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("読み込んだ行 -> %s", line);
		free(line); // メモリリークを防ぐ [cite: 19]
	}

	printf("入力が終了しました。\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:49:30 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/15 21:20:17 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *rest)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;
	char	*tmp;

	bytes = 1;
	while (!ft_strchr(rest, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
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

static char	*extract_line(char *rest)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!rest || !*rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
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
	size_t	i;
	char	*new_rest;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	new_rest = ft_strdup(rest + i);
	free(rest);
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_until_newline(fd, rest);
	if (!rest)
		return (NULL);
	line = extract_line(rest);
	rest = update_rest(rest);
	return (line);
}

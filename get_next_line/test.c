/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:41:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 19:39:27 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hoge.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	close(fd);
	return (0);
}

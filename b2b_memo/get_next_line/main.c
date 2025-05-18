/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:35 by kishigam          #+#    #+#             */
/*   Updated: 2022/07/17 08:14:18 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
    int fd;
    char *s;

	fd = open("./text.txt", O_RDONLY);

	s = get_next_line(fd);
    printf("%s", s);
    free(s);
    s = get_next_line(fd);
    printf("%s", s);
    free(s);
    s = get_next_line(fd);
    printf("%s", s);
    free(s);
    s = get_next_line(fd);
    printf("%s", s);
    free(s);
    s = get_next_line(fd);
    printf("%s", s);
    free(s);
    close(fd);
    system("leaks a.out");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/07 19:05:51 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 09:52:37 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int	pf_putchar(int c)
{
	return (write(1, &c, 1));
}

// int	pf_putchar(int c)
// {
// 	ssize_t ret;
// 	ret = write(1, &c, 1);
// 	if(ret < 0);
// 		return(-1);
// 	return (1);
// }
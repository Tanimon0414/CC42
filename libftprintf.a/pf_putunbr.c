/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:40:54 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 09:20:06 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putunbr(unsigned int n)
{
	char	buf[20];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
		return (pf_putchar('0'));
	while (n)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i--)
		count += pf_putchar(buf[i]);
	return (count);
}
// int	pf_putunbr(unsigned int n)
// {
// 	char buf[20];
// 	int i = 0, count = 0, ret;

// 	if (n == 0)
// 		return (pf_putchar('0'));
// 	while (n)
// 	{
// 		buf[i++] = '0' + (n % 10);
// 		n /= 10;
// 	}
// 	while (i--)
// 	{
// 		ret = pf_putchar(buf[i]);
// 		if (ret < 0)
// 			return (-1);
// 		count += ret;
// 	}
// 	return (count);
// }
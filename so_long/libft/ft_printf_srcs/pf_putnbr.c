/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:40:46 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 16:50:50 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putnbr(long n)
{
	char	buf[20];
	int		i;
	int		count;
	long	nb;

	i = 0;
	count = 0;
	nb = n;
	if (n == 0)
		return (pf_putchar('0'));
	if (n < 0)
	{
		count += pf_putchar('-');
		nb = -nb;
	}
	while (nb)
	{
		buf[i++] = '0' + (nb % 10);
		nb /= 10;
	}
	while (i--)
		count += pf_putchar(buf[i]);
	return (count);
}
// int	pf_putnbr(long n)
// {
// 	char buf[20];
// 	int i = 0, count = 0, ret;
// 	long nb = n;

// 	if (n == 0)
// 		return (pf_putchar('0'));
// 	if (n < 0)
// 	{
// 		ret = pf_putchar('-');
// 		if (ret < 0)
// 			return (-1);
// 		count += ret;
// 		nb = -nb;
// 	}
// 	while (nb)
// 	{
// 		buf[i++] = '0' + (nb % 10);
// 		nb /= 10;
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
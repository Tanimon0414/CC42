/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:43:57 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 09:20:23 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_puthex(unsigned long n, int upper)
{
	int			i;
	int			count;
	const char	*digits;
	char		buf[20];

	if (upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	i = 0;
	count = 0;
	if (n == 0)
		return (pf_putchar('0'));
	while (n)
	{
		buf[i++] = digits[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		count += pf_putchar(buf[i]);
	return (count);
}
// int	pf_puthex(unsigned long n, int uppercase)
// {
// 	char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
// 	char buf[20];
// 	int i = 0, count = 0, ret;

// 	if (n == 0)
// 		return (pf_putchar('0'));
// 	while (n)
// 	{
// 		buf[i++] = digits[n % 16];
// 		n /= 16;
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
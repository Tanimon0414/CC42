/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:40:51 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 09:19:17 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	pf_putstr(const char *s)
{
	int	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
// int	pf_putstr(char *s)
// {
// 	int count = 0;
// 	int ret;

// 	if (!s)
// 		s = "(null)";
// 	while (*s)
// 	{
// 		ret = pf_putchar(*s++);
// 		if (ret < 0)
// 			return (-1);
// 		count += ret;
// 	}
// 	return (count);
// }
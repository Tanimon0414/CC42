/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:18:26 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 15:25:04 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putptr(void *p)
{
	int	count;

	count = 0;
	if (p == NULL)
		return (pf_putstr("(nil)"));
	count += pf_putstr("0x");
	count += pf_puthex((uintptr_t)p, 0);
	return (count);
}
// int	pf_putptr(void *p)
// {
// 	int count = 0, ret;

// 	if (p == NULL)
// 		return (pf_putstr("(nil)"));
// 	ret = pf_putstr("0x");
// 	if (ret < 0)
// 		return (-1);
// 	count += ret;
// 	ret = pf_puthex((uintptr_t)p, 0);
// 	if (ret < 0)
// 		return (-1);
// 	count += ret;
// 	return (count);
// }
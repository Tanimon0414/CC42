/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:16:12 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 13:06:19 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol_strict(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0' || !(*str >= '0' && *str <= '9'))
		return ((long)INT_MAX + 1L);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');//*str = "002"とかもエラーとして返すように設定する
		str++;
	}
	if (*str != '\0')
		return ((long)INT_MAX + 1L);
	if ((sign == 1 && res > LONG_MAX))
		//ホントはもっとちゃんとしたエラーチェックが必要
		return ((long)INT_MAX + 1L);
	return (res * sign);
}

int ft_min(int n1, int n2)
{
	if(n1 <= n2)
		return(n1);
	else
		return(n2);
}

int ft_max(int n1, int n2)
{
	if(n1<= n2)
		return(n2);
	else
		return(n1);
}

int ft_abs(int n)
{
	if(n < 0)
		n = -n;
	return(n);
}

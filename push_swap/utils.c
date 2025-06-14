/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:16:12 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/13 17:05:05 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	strict_atoi(const char *str, int *out)
{
	long long	acc;
	int			sign;
	int			digit;

	acc = 0;
	sign = 1;
	if (!str || !*str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit((unsigned char)*str))
		return (0);
	while (ft_isdigit((unsigned char)*str))
	{
		digit = *str - '0';
		if (sign == 1)
		{
			if (acc > (INT_MAX - digit) / 10)
				return (0); /* 正側オーバーフロー */
		}
		else
		{
			/* INT_MIN = -2147483648 → 1 多い分だけ範囲を拡張して判定 */
			if (acc > ((-(long long)INT_MIN) - digit) / 10)
				return (0); /* 負側オーバーフロー */
		}
		acc = acc * 10 + digit;
		str++;
	}
	/* 5. 末尾に数字以外の文字が残っていればエラー */
	if (*str != '\0')
		return (0);
	*out = (int)(sign == 1 ? acc : -acc);
	return (1);
}

int	ft_min(int n1, int n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
}

int	ft_max(int n1, int n2)
{
	if (n1 <= n2)
		return (n2);
	else
		return (n1);
}

int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

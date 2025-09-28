/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:19 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:20 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_result(int n, size_t len, int sign, char *result)
{
	long long	num;
	size_t		i;

	if (n == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	if (sign)
	{
		result[0] = '-';
		num = -(long long)n;
	}
	else
		num = n;
	result[len] = '\0';
	i = len - 1;
	while (num > 0)
	{
		result[i--] = '0' + (num % 10);
		num /= 10;
	}
	return (result);
}

static size_t	count_length(int n)
{
	size_t		len;
	long long	num;

	len = 0;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	num = n;
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;
	int		sign;
	size_t	i;

	if (n == -2147483648)
	{
		result = (char *)malloc(sizeof(char) * 12);
		if (!result)
			return (NULL);
		return (ft_strcpy(result, "-2147483648"));
	}
	sign = (n < 0);
	len = count_length(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i <= len)
		result[i++] = '\0';
	return (make_result(n, len, sign, result));
}

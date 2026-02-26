/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:14 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:15 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_numeric_error(const char *c)
{
	write(1, "exit\n", 5);
	put_error_str("exit: ", (char *)c, ": numeric argument required\n");
	exit(2);
}

static long long	parse_numeric_part(const char *c, int *i)
{
	long long	result;
	long long	tmp;

	result = 0;
	while (c[*i])
	{
		if (!(c[*i] >= '0' && c[*i] <= '9'))
			handle_numeric_error(c);
		tmp = result;
		result = result * 10 + (c[*i] - '0');
		if (result / 10 != tmp)
			handle_numeric_error(c);
		(*i)++;
	}
	return (result);
}

long long	ft_atoll(char *c)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	while (c[i] == ' ' || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			sign = -1;
		i++;
	}
	result = parse_numeric_part(c, &i);
	printf("exit\n");
	return (result * sign);
}

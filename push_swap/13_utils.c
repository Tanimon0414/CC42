/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:16:12 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 14:24:51 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

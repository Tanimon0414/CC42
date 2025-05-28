/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 08:21:17 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/10 09:15:02 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*int_to_str(int n, int pow_ten, short sign, char *out)
{
	size_t	i;

	i = 0;
	if (sign == -1)
		i++;
	while (pow_ten)
	{
		out[i++] = (char)(n / pow_ten * sign + '0');
		n %= pow_ten;
		pow_ten /= 10;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*out;
	short	sign;
	int		pow_ten;

	i = 1;
	pow_ten = 1;
	sign = 0;
	if (n < 0)
		sign++;
	while (n / pow_ten / 10 && i++)
		pow_ten *= 10;
	out = (char *)malloc(i + sign + 1);
	if (!out)
		return (NULL);
	if (sign == 1)
	{
		out[0] = '-';
		sign = -1;
	}
	else
		sign++;
	return (int_to_str(n, pow_ten, sign, out));
}

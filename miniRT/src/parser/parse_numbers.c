/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses and consumes an optional sign character. */
static int	read_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

/* Reads an unsigned integer part as double and reports digit presence. */
static int	read_intpart(const char *s, int *i, double *val)
{
	int	digits;

	digits = 0;
	*val = 0.0;
	while (ft_isdigit(s[*i]))
	{
		*val = *val * 10.0 + (s[*i] - '0');
		(*i)++;
		digits = 1;
	}
	return (digits);
}

/* Reads optional fraction part and returns whether it had digits. */
static int	read_fraction(const char *s, int *i, double *frac)
{
	double	num;
	double	den;
	int		digits;

	num = 0.0;
	den = 1.0;
	digits = 0;
	*frac = 0.0;
	if (s[*i] != '.')
		return (0);
	(*i)++;
	while (ft_isdigit(s[*i]))
	{
		num = num * 10.0 + (s[*i] - '0');
		den *= 10.0;
		(*i)++;
		digits = 1;
	}
	*frac = num / den;
	return (digits);
}

/* Parses a decimal string into double without exponent syntax. */
int	parse_double(const char *s, double *out)
{
	int		i;
	int		sign;
	int		digits;
	double	intpart;
	double	frac;

	if (!s || !s[0])
		return (1);
	i = 0;
	sign = read_sign(s, &i);
	digits = read_intpart(s, &i, &intpart);
	digits += read_fraction(s, &i, &frac);
	if (!digits || s[i] != '\0')
		return (1);
	*out = (intpart + frac) * sign;
	return (0);
}

/* Parses a decimal integer string into int with range checks. */
int	parse_int(const char *s, int *out)
{
	int		i;
	int		sign;
	long	val;

	if (!s || !s[0])
		return (1);
	i = 0;
	sign = read_sign(s, &i);
	if (!ft_isdigit(s[i]))
		return (1);
	val = 0;
	while (ft_isdigit(s[i]))
	{
		val = val * 10 + (s[i++] - '0');
		if ((sign == 1 && val > INT_MAX)
			|| (sign == -1 && val > (long)INT_MAX + 1))
			return (1);
	}
	if (s[i] != '\0')
		return (1);
	*out = (int)(val * sign);
	return (0);
}

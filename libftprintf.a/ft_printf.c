/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:44:42 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/11 09:21:19 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	dispatch(const char **fmt, va_list ap)
{
	if (**fmt == 'c')
		return (pf_putchar(va_arg(ap, int)));
	else if (**fmt == 's')
		return (pf_putstr(va_arg(ap, char *)));
	else if (**fmt == 'p')
		return (pf_putptr(va_arg(ap, void *)));
	else if (**fmt == 'd' || **fmt == 'i')
		return (pf_putnbr(va_arg(ap, int)));
	else if (**fmt == 'u')
		return (pf_putunbr(va_arg(ap, unsigned int)));
	else if (**fmt == 'x')
		return (pf_puthex(va_arg(ap, unsigned int), 0));
	else if (**fmt == 'X')
		return (pf_puthex(va_arg(ap, unsigned int), 1));
	else if (**fmt == '%')
		return (pf_putchar('%'));
	else
		return (pf_putchar(**fmt));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		total;

	total = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			total += dispatch(&format, ap);
		}
		else
			total += pf_putchar(*format);
		format++;
	}
	va_end(ap);
	return (total);
}
// int	ft_printf(const char *format, ...)
// {
// 	va_list ap;
// 	int total = 0;
// 	int ret;

// 	va_start(ap, format);
// 	while (*format)
// 	{
// 		if (*format == '%' && *(format + 1))
// 		{
// 			format++;
// 			ret = dispatch(&format, ap);
// 		}
// 		else
// 		{
// 			ret = pf_putchar(*format);
// 		}
// 		if (ret < 0)
// 		{
// 			va_end(ap);
// 			return (-1);
// 		}
// 		total += ret;
// 		format++;
// 	}
// 	va_end(ap);
// 	return (total);
// }
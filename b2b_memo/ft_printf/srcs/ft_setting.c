/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:58:48 by kishigam          #+#    #+#             */
/*   Updated: 2022/06/12 12:40:16 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

int	ft_putptr(void *ptr)
{
	unsigned long long	hex;
	int					len;

	hex = (unsigned long long)ptr;
	len = 0;
	if (hex >= 16)
		len += ft_putptr((void *)(hex / 16));
	len += ft_putchar("0123456789abcdef"[hex % 16]);
	return (len);
}

int	ft_putint(int num)
{
	int		len;
	char	*num_str;

	num_str = ft_itoa(num);
	len = ft_putstr(num_str);
	free(num_str);
	return (len);
}

int	ft_putuint(unsigned int num)
{
	int	len;

	len = 0;
	if (num >= 10)
		len += ft_putuint(num / 10);
	len += write(1, &"0123456789"[num % 10], 1);
	return (len);
}

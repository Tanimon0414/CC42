/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:02:53 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/10 21:00:53 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

int	pf_putchar(int c);
int	pf_putstr(const char *s);
int	pf_putnbr(long n);
int	pf_putunbr(unsigned int n);
int	pf_puthex(unsigned long n, int upper);
int	pf_putptr(void *p);

#endif

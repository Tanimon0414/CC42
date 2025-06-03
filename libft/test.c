/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:24:04 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/01 09:18:39 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// test.c
#include "libft.h"  // libft.h が ft_printf.h をインクルードしている想定
#include <limits.h> // INT_MIN, INT_MAX などのテスト用
#include <stdio.h>  // 本家 printf との比較用

int	main(void)
{
	char *str = "Hello World";
	printf("%s\n", str);
	ft_printf("%s\n", str);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:24:04 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/31 20:59:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// test.c
#include "libft.h"  // libft.h が ft_printf.h をインクルードしている想定
#include <limits.h> // INT_MIN, INT_MAX などのテスト用
#include <stdio.h>  // 本家 printf との比較用

int	main(void)
{
	printf("Hello World\n");
	ft_printf("Hello World\n");
	return (0);
}
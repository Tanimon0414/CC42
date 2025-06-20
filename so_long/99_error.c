/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:59:03 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/20 12:03:45 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_with_error(char *message)
{
	ft_putstr_fd("Error\n", 2); // 課題の要求通り "Error\n" を先に出力
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

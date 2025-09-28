/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:46:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 16:46:50 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleanup_and_exit(t_data *data, const char *error_msg)
{
	printf("%s\n", error_msg);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	// 他にも確保したものがあればここで解放
	return (1);
}

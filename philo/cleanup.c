/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Destroy mutexes and free every allocation kept in t_data. */
void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_ready)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < data->forks_ready)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->write_ready)
		pthread_mutex_destroy(&data->write_lock);
	if (data->data_ready)
		pthread_mutex_destroy(&data->data_lock);
	free(data->philos);
	free(data->forks);
}

/* Join only successfully created threads. */
int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->threads_ready)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

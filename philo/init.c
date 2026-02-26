/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:46:21 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialize every fork mutex and global synchronization mutexes. */
bool	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		data->forks_ready++;
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (false);
	data->write_ready = 1;
	if (pthread_mutex_init(&data->data_lock, NULL) != 0)
		return (false);
	data->data_ready = 1;
	return (true);
}

/* Philosopher i uses fork i and fork (i + 1) % n. */
static void	assign_forks(t_data *data, int i)
{
	data->philos[i].l_fork = &data->forks[i];
	data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
}

/* Initialize philosopher metadata and per-philosopher meal mutexes. */
bool	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = 0;
		assign_forks(data, i);
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (false);
		data->philos_ready++;
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:46:21 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 17:29:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	if (data->start_time == 0)
		return (false);
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_cont = 0;
		data->philos[i].last_meal_time = data->start_time;
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].l_fork = &data->forks[i];
			data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
		}
		else
		{
			data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
			data->philos[i].r_fork = &data->forks[i];
		}
		i++;
	}
	return (true);
}

bool	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->data_lock, NULL) != 0)
		return (false);
	return (true);
}

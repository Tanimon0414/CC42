/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_finished(t_data *data)
{
	pthread_mutex_lock(&data->data_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->data_lock);
}

/* Detect starvation and print death log exactly once. */
static bool	check_death(t_philo *philo)
{
	uint64_t	now;
	uint64_t	last_meal;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	now = get_time_ms();
	if (now == 0)
		return (false);
	if (diff_ms(now, last_meal) < philo->data->death_time)
		return (false);
	pthread_mutex_lock(&philo->data->data_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->data_lock);
		return (true);
	}
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->data_lock);
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%llu %d died\n",
		(unsigned long long)diff_ms(now, philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (true);
}

/* Optional stopping condition: everyone ate meals_nb times. */
static bool	check_all_ate(t_data *data)
{
	int	i;
	int	done;

	if (data->meals_nb < 0)
		return (false);
	i = 0;
	done = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].eat_count >= data->meals_nb)
			done++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (done == data->philo_num)
	{
		set_finished(data);
		return (true);
	}
	return (false);
}

/* Monitor starvation or optional meal target completion. */
void	monitor(t_data *data)
{
	int	i;

	while (!is_simulation_finished(data))
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (check_death(&data->philos[i]))
				return ;
			i++;
		}
		if (check_all_ate(data))
			return ;
		usleep(500);
	}
}

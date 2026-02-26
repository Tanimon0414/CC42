/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:42:38 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Lock two forks in a deterministic order to avoid deadlock cycles. */
static bool	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->id % 2 == 0)
		first = philo->r_fork;
	if (philo->id % 2 == 0)
		second = philo->l_fork;
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork");
	if (is_simulation_finished(philo->data))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
	return (true);
}

/* Update meal state while both forks are locked. */
static void	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	smart_sleep(philo->data, philo->data->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/* Special case: one philosopher can only take one fork and starve. */
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->philo_num == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		while (!is_simulation_finished(philo->data))
			usleep(200);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	while (!is_simulation_finished(philo->data))
	{
		eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo->data, philo->data->sleep_time);
		print_status(philo, "is thinking");
		if (philo->data->philo_num % 2 == 1)
			smart_sleep(philo->data, philo->data->eat_time / 2);
	}
	return (NULL);
}

/* Create all philosopher threads and store start timestamp. */
bool	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	if (data->start_time == 0)
		return (false);
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philosopher_routine,
				&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->data_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->data_lock);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			data->threads_ready = 0;
			return (false);
		}
		data->threads_ready++;
		i++;
	}
	return (true);
}

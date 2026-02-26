/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:19:04 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 17:19:20 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	diff_ms(uint64_t now, uint64_t past)
{
	if (now <= past)
		return (0);
	return (now - past);
}

/* Read termination flag under mutex to avoid data races. */
bool	is_simulation_finished(t_data *data)
{
	bool	finished;

	pthread_mutex_lock(&data->data_lock);
	finished = (data->dead != 0);
	pthread_mutex_unlock(&data->data_lock);
	return (finished);
}

/* Serialize logs and stop printing after simulation end. */
void	print_status(t_philo *philo, const char *status)
{
	uint64_t	now;
	uint64_t	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->data_lock);
	if (!philo->data->dead)
	{
		now = get_time_ms();
		timestamp = diff_ms(now, philo->data->start_time);
		printf("%llu %d %s\n",
			(unsigned long long)timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->data_lock);
	pthread_mutex_unlock(&philo->data->write_lock);
}

/* Sleep in short slices so thread reacts quickly to stop condition. */
void	smart_sleep(t_data *data, uint64_t duration_ms)
{
	uint64_t	start;

	start = get_time_ms();
	while (!is_simulation_finished(data))
	{
		if (get_time_ms() - start >= duration_ms)
			break ;
		usleep(200);
	}
}

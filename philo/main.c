/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:45:09 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Entry point: parse -> init -> run -> monitor -> join -> cleanup. */
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Error: Invalid arguments\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (!set_args(&data, av, ac))
		return (printf("Error: Invalid argument value\n"), 1);
	data.philos = malloc(sizeof(t_philo) * data.philo_num);
	if (!data.philos)
		return (cleanup_and_exit(&data, "Error: malloc failed"));
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_num);
	if (!data.forks)
		return (cleanup_and_exit(&data, "Error: malloc failed"));
	if (!init_mutexes(&data) || !init_philosophers(&data)
		|| !start_simulation(&data))
		return (cleanup_and_exit(&data, "Error: initialization failed"));
	monitor(&data);
	if (join_threads(&data) != 0)
		return (cleanup_and_exit(&data, "Error: thread join failed"));
	cleanup(&data);
	return (0);
}

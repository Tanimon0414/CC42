/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:45:09 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 18:32:17 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (cleanup_and_return(&data, "Error: Malloc for philos failed"));
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_num);
	if (data.forks == NULL)
		return (cleanup_and_exit(&data, "Error: Malloc for forks failed"));
	//他にも処理
	if (!init_mutexes(&data))
		return (cleanup_and_exit(&data, "Error: Mutex init failed\n"));
	if (!init_philosophers(&data))
		return (cleanup_and_exit(&data, "Error: Mutex init failed\n"));
	if (!start_simulation(&data))
		return (cleanup_and_exit(&data, "Error: Mutex init failed\n"));
	free(data.philos);
	free(data.forks);
	return (0);
}

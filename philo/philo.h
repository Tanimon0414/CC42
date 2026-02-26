/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:45:25 by atanimot          #+#    #+#             */
/*   Updated: 2026/02/25 00:00:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eat_count;
	uint64_t		last_meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}	t_philo;

/* Shared simulation state accessed by all philosopher threads. */
struct s_data
{
	int				philo_num;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				meals_nb;
	uint64_t		start_time;
	int				dead;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	data_lock;
	int				forks_ready;
	int				philos_ready;
	int				threads_ready;
	int				write_ready;
	int				data_ready;
};

/* parse.c */
bool		set_args(t_data *data, char **av, int ac);
/* init.c */
bool		init_mutexes(t_data *data);
bool		init_philosophers(t_data *data);
/* simulate.c */
bool		start_simulation(t_data *data);
void		*philosopher_routine(void *arg);
/* monitor.c */
void		monitor(t_data *data);
/* cleanup.c */
int			join_threads(t_data *data);
/* utils.c */
bool		is_simulation_finished(t_data *data);
uint64_t	get_time_ms(void);
uint64_t	diff_ms(uint64_t now, uint64_t past);
void		smart_sleep(t_data *data, uint64_t duration_ms);
void		print_status(t_philo *philo, const char *status);
/* parse.c */
bool		ft_parse_uint64(const char *str, uint64_t *dest);
/* cleanup.c */
void		cleanup(t_data *data);
/* error.c */
int			cleanup_and_exit(t_data *data, const char *error_msg);

#endif

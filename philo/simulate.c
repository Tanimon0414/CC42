/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:42:38 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 18:36:22 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_simulation_finished(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->data_lock);
	result = (data->dead == 1);
	pthread_mutex_unlock(&data->data_lock);
	retunr(result);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	// ここに哲学者の行動ループ（食事、睡眠、思考）を実装します
	// while ( philo->data->dead == 0 ) {... } のような形になるでしょう
	while (!is_simulation_finished(philo->data))
	{
		// ここに食事(eat)、睡眠(sleep)、思考(think)の処理を実装する
		// eat(philo);
		// sleep(philo);
		// think(philo);
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].t1, NULL, &philosopher_routine,
				&data->philos[i]) != 0)
		{
			// スレッド生成に失敗した場合のエラー処理
			// (ここに来る前に生成したスレッドをjoinして待つなど、本当はもっと丁寧な処理が必要)
			return (false);
		}
		i++;
	}
	return (true);
}

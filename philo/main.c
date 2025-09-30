/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:45:09 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/30 17:08:56 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 確保した全てのリソースを解放する関数
void cleanup(t_data *data)
{
    int i;

    // 1. ミューテックスの破棄
    i = 0;
    while (i < data->philo_num)
    {
        // フォーク用ミューテックス
        pthread_mutex_destroy(&data->forks[i]);
        // 哲学者個人のロック用ミューテックス
        pthread_mutex_destroy(&data->philos[i].lock);
        i++;
    }
    // 共有データ保護用ミューテックス
    pthread_mutex_destroy(&data->data_lock);
    // ログ出力保護用ミューテックス
    pthread_mutex_destroy(&data->write_lock);

    // 2. 動的メモリの解放
    // (注: forks配列を先に解放するとphilosからアクセスできなくなる可能性があるため、
    //  依存関係のないものから解放するのが安全)
    if (data->philos)
        free(data->philos);
    if (data->forks)
        free(data->forks);
}

// 哲学者が死んでいないかチェックする関数
static bool check_death(t_philo *philo)
{
    uint64_t current_time;

    // 哲学者個人のデータを保護するミューテックスをロック
    pthread_mutex_lock(&philo->lock);

    current_time = get_time_ms();
    if ((current_time - philo->last_meal_time) >= philo->data->death_time)
    {
        // 哲学者個人のデータをアンロックしてから、共有フラグを更新
        pthread_mutex_unlock(&philo->lock);

        // --- 共有フラグの更新 ---
        pthread_mutex_lock(&philo->data->data_lock);
        philo->data->dead = 1;
        pthread_mutex_unlock(&philo->data->data_lock);
        // --- 共有フラグの更新終了 ---

        print_status(philo, "died");
        return (true); // 誰かが死んだ
    }

    // 哲学者個人のデータを保護するミューテックスをアンロック
    pthread_mutex_unlock(&philo->lock);
    return (false); // まだ生きている
}

// 全員が規定回数食べ終わったかチェックする関数
static bool check_all_ate(t_data *data)
{
    int i = 0;
    int finished_philos = 0;

    // 食事回数オプションが有効でない場合はチェックしない
    if (data->meals_nb == -1)
        return (false);

    while (i < data->philo_num)
    {
        pthread_mutex_lock(&data->philos[i].lock);
        if (data->philos[i].eat_cont >= data->meals_nb)
            finished_philos++;
        pthread_mutex_unlock(&data->philos[i].lock);
        i++;
    }

    if (finished_philos == data->philo_num)
    {
        pthread_mutex_lock(&data->data_lock);
        data->dead = 1; // deadフラグを終了条件として再利用
        pthread_mutex_unlock(&data->data_lock);
        return (true); // 全員食べ終わった
    }
    return (false);
}

// 監視役のメインループ
void monitor(t_data *data)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < data->philo_num)
        {
            if (check_death(&data->philos[i]))
                return; // 誰かが死んだら監視終了
            i++;
        }
        if (check_all_ate(data))
            return; // 全員食べ終わったら監視終了

        usleep(1000); // CPUを過剰に消費しないように少し待機
    }
}

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
	// 監視役ループを開始
    monitor(&data);
	// 全ての哲学者スレッドが終了するのを待つ
	int i = 0;
	while (i < data.philo_num)
	{
    	// data.philos[i].t1 に格納されているスレッドIDを指定して待機
    	if (pthread_join(data.philos[i].t1, NULL)!= 0)
    	{
        // エラー処理 (通常はここでのエラーは深刻)
        // return an error
    	}
    	i++;
	}
	// 全てのリソースを解放
    cleanup(&data);
	free(data.philos);
	free(data.forks);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:42:38 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/30 17:00:51 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 哲学者の状態をタイムスタンプ付きで安全に出力する関数
void print_status(t_philo *philo, const char *status)
{
    uint64_t time;

    // ログ出力用のミューテックスをロック
    pthread_mutex_lock(&philo->data->write_lock);

    // 現在時刻を取得 (シミュレーション開始からの経過時間)
    time = get_time_ms() - philo->data->start_time;

    // 誰かが死んでいなければ出力する
    if (!is_simulation_finished(philo->data))
    {
        printf("%llu %d %s\n", time, philo->id, status);
    }

    // ログ出力用のミューテックスをアンロック
    pthread_mutex_unlock(&philo->data->write_lock);
}

static bool	is_simulation_finished(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->data_lock);
	result = (data->dead == 1);
	pthread_mutex_unlock(&data->data_lock);
	return(result);
}

static void take_forks(t_philo *philo)
{
    // 初期化時にデッドロック回避のため順序付けしたフォークを取る
    pthread_mutex_lock(philo->l_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->r_fork);
    print_status(philo, "has taken a fork");
}

static void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

static void eat(t_philo *philo)
{
    take_forks(philo);

    // --- クリティカルセクション (データ更新) ---
    // 哲学者個人のデータを保護するミューテックスをロック
    pthread_mutex_lock(&philo->lock);

    print_status(philo, "is eating");
    philo->last_meal_time = get_time_ms(); // 最後の食事時刻を更新
    philo->eat_cont++;                   // 食事回数をインクリメント

    // 哲学者個人のデータを保護するミューテックスをアンロック
    pthread_mutex_unlock(&philo->lock);
    // --- クリティカルセクション終了 ---

    usleep(philo->data->eat_time * 1000); // 食事時間をシミュレート

    drop_forks(philo);
}

static void philo_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->sleep_time * 1000);
}

static void think(t_philo *philo)
{
    print_status(philo, "is thinking");
}



void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);

    while (!is_simulation_finished(philo->data))
    {
        eat(philo);
        philo_sleep(philo);
        think(philo);
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

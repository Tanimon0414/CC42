/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:45:25 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/30 17:17:46 by atanimot         ###   ########.fr       */
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

// 1. s_data構造体の存在を先に知らせる (前方宣言)
struct s_data;

typedef struct s_data
{
	int				philo_num;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int meals_nb;        //(オプション) 各哲学者が食べるべき回数 。
	uint64_t start_time; //シミュレーション開始時刻のタイムスタンプ。
	//全ての時間計算の基準点となります
	int				dead;
	int				finished;
	pthread_mutex_t *forks; //フォークを表すミューテックスの配列。
							//哲学者の数と同じ要素数を持ちます
	t_philo			*philos;
	pthread_mutex_t	lock;
	// deadやfinishedといった共有フラグを読み書きする際のデータ競合を防ぐためのMutex。
	pthread_mutex_t write;      // printfによるログ出力が混ざらないようにするためのMutex。
	pthread_mutex_t write_lock; //ログ出力保護用
	pthread_mutex_t data_lock;  //共有データ保護用
}					t_data;

typedef struct s_philo
{
	int id;       //哲学者の番号 (1からphilo_numまで) 。
	pthread_t t1; //この哲学者を実行するスレッドの識別子 。
	int				eat_cont;
	uint64_t		last_meal_time;
	//最後に食事を開始した時刻のタイムスタンプ。監視役は現在の時刻とこの値を比較して、
	//餓死していないかを確認します 。
	int eating; // 現在、食事中であるかを示すフラグ
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	// この哲学者個人のデータ（特にtime_to_dieやeat_cont）を保護するためのMutex。
	//監視スレッドがこれらの値を読み取る際と、哲学者スレッドが書き込む際にデータ競合
	//が起きるのを防ぎます 。
	t_data *data; //全体管理用構造体へのポインタ。これにより、共有情報
					//（deadフラグや時間設定など）にアクセスできます 。
}					t_philo;

/* --- Function Prototypes --- */

// init.c - 初期化関連
bool        set_args(t_data *data, char **av, int ac);
bool        init_mutexes(t_data *data);
bool        init_philosophers(t_data *data);

// simulation.c - シミュレーション実行関連
bool        start_simulation(t_data *data);
void        *philosopher_routine(void *arg);

// monitor.c - 監視役関連
void        monitor(t_data *data);
bool        is_simulation_finished(t_data *data);

// utils.c - ユーティリティ関数
uint64_t    get_time_ms(void);
void        print_status(t_philo *philo, const char *status);
bool        ft_parse_uint64(const char *str, uint64_t *dest);

// cleanup.c - 解放処理関連
void        cleanup(t_data *data);
int         cleanup_and_exit(t_data *data, const char *error_msg);


#endif

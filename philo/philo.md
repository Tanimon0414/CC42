# philosophers 実装メモ (提出用)

## 1. このプログラムの目的
- 食事哲学者問題を `pthread` と `mutex` で実装する。
- データ競合を起こさずに、以下の状態をログ表示する。
  - `has taken a fork`
  - `is eating`
  - `is sleeping`
  - `is thinking`
  - `died`

## 2. 引数
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
        [number_of_times_each_philosopher_must_eat]
```

- 全てミリ秒単位。
- 5番目の引数は任意。
- 任意引数ありの場合、全員が指定回数食べたら終了。

## 3. 全体の流れ
```text
main
  -> set_args           (引数チェック)
  -> malloc             (philos, forks)
  -> init_mutexes       (fork mutex + global mutex)
  -> init_philosophers  (各哲学者の初期化)
  -> start_simulation   (全スレッド起動)
  -> monitor            (死亡/完食条件を監視)
  -> join_threads       (全スレッド終了待ち)
  -> cleanup            (mutex破棄 + free)
```

## 4. 構造体

### `t_data` (共有状態)
- `philo_num`: 哲学者人数
- `death_time`, `eat_time`, `sleep_time`: 各時間
- `meals_nb`: 任意の食事回数条件
- `start_time`: シミュレーション開始時刻
- `dead`: 終了フラグ (死亡または全員完食)
- `forks`: フォーク mutex 配列
- `philos`: 哲学者配列
- `write_lock`: ログ出力保護
- `data_lock`: 共有フラグ保護
- `*_ready`: 初期化済み数 (異常時 cleanup 用)

### `t_philo` (哲学者1人分)
- `id`: 1始まりID
- `thread`: スレッドID
- `eat_count`: 食事回数
- `last_meal_time`: 最後に食べ始めた時刻
- `l_fork`, `r_fork`: 両隣フォーク
- `meal_lock`: `eat_count` / `last_meal_time` 保護
- `data`: 共有状態への参照

## 5. ファイルごとの責務

### `main.c`
- 起動順序の制御だけを担当。

### `parse.c`
- `ft_parse_uint64`: 文字列を `uint64_t` に安全変換。
- `set_args`: 引数を構造体に設定、値を検証。

### `init.c`
- `init_mutexes`: fork mutex と共有 mutex を作成。
- `init_philosophers`: 各哲学者の初期値と fork 参照を設定。

### `simulate.c`
- `philosopher_routine`: eat -> sleep -> think のループ。
- `take_forks`: 2本のフォークを決まった順序で取得。
- `start_simulation`: 全哲学者スレッドを作成。

### `monitor.c`
- `check_death`: 飢餓死検出、`died` を1回だけ表示。
- `check_all_ate`: 任意条件「全員規定回数食べた」を検出。
- `monitor`: 上記2条件を周期監視。

### `utils.c`
- `get_time_ms`: 現在時刻(ms)取得。
- `is_simulation_finished`: 終了フラグをmutex付きで読む。
- `print_status`: ログをmutex付きで安全出力。
- `smart_sleep`: 短い sleep を繰り返して終了に素早く反応。

### `cleanup.c`
- `join_threads`: 生成済みスレッドの `pthread_join`。
- `cleanup`: mutex破棄とメモリ解放。

### `error.c`
- `cleanup_and_exit`: エラー表示 + cleanup + `1` を返す。

## 6. 競合を防ぐポイント
- `write_lock`: `printf` 行の混線防止。
- `data_lock`: 終了フラグ `dead` の読み書き保護。
- `meal_lock`: `last_meal_time` と `eat_count` を保護。

## 7. デッドロック対策
- フォーク取得順を「ポインタの小さい方 -> 大きい方」に固定。
- 循環待ちを作らないため、取得順の全体一貫性を維持。

## 8. 1人ケース
- フォークを1本だけ取って待機。
- `time_to_die` 到達で監視側が `died` を表示して終了。

## 9. 使用している外部関数 (importした関数)

### 標準ライブラリ系
- `printf`
- `malloc`, `free`
- `memset`
- `usleep`
- `gettimeofday`

### pthread系
- `pthread_create`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

## 10. 動作確認例
```bash
make
./philo 1 800 200 200
./philo 2 800 200 200 3
./philo 5 800 200 200 3
```

## 11. 初見の人向けの読み順
1. `main.c` で全体フローを見る
2. `philo.h` で構造体を見る
3. `simulate.c` と `monitor.c` で本体ロジックを見る
4. `utils.c` のロック付きユーティリティを見る
5. `cleanup.c` で終了処理を見る

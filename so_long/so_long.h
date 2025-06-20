/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:01:58 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/20 14:05:12 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* --- 定数 --- */
# define TILE_SIZE 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# define EVENT_KEY_PRESS 2
# define EVENT_DESTROY 17

/* --- 構造体 --- */

// BFSでの座標管理用にt_point構造体を定義
typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		p_count;
	int		c_count;
	int		e_count;
	int		p_x;
	int		p_y;
}			t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	img;
	int		move_count;
}			t_game;

typedef struct s_queue
{
	t_point	*points;
	int		front;
	int		rear;
	int		capacity;
}			t_queue;

typedef struct s_bfs
{
	t_queue	*queue;
	char	**visited;
	int		found_c;
	int		found_e;
}			t_bfs;

typedef struct s_directions
{
	int		dx[4];
	int		dy[4];
}			t_directions;

/* --- 関数プロトタイプ --- */

/* init.c */
void		init_game(t_game *game, t_map *map);
void		start_mlx(t_game *game);

/* render.c */
int			render_game(t_game *game);

/* game.c */
int			handle_keypress(int keycode, t_game *game);

/* cleanup.c */
int			close_game(t_game *game);
void		free_grid(char **grid);

/* parser.c */
t_map		*parse_map(int argc, char **argv);

/* validator.c */
void		check_map_components(t_map *map);
void		check_walls(t_map *map);
void		check_path(t_map *map);

/* queue_utils.c */
t_queue		*create_queue(int capacity);
void		enqueue(t_queue *q, int x, int y);
t_point		dequeue(t_queue *q);

/* error.c */
void		exit_with_error(char *message);

#endif
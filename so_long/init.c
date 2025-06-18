/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:57:09 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/18 16:57:45 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_single_texture(t_game *game, char *path)
{
	void	*img;
	int		size;

	size = TILE_SIZE;
	img = mlx_xpm_file_to_image(game->mlx, path, &size, &size);
	if (!img)
		exit_with_error("Error: Failed to load texture.");
	return (img);
}

static void	load_textures(t_game *game)
{
	game->img.wall = load_single_texture(game, "textures/wall.xpm");
	game->img.floor = load_single_texture(game, "textures/floor.xpm");
	game->img.player = load_single_texture(game, "textures/player.xpm");
	game->img.collectible = load_single_texture(game,
			"textures/collectible.xpm");
	game->img.exit = load_single_texture(game, "textures/exit.xpm");
}

void	init_game(t_game *game, t_map *map)
{
	game->map = map;
	game->move_count = 0;
	game->mlx = NULL;
	game->win = NULL;
}

void	start_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_with_error("Error: mlx_init() failed.");
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long");
	if (!game->win)
		exit_with_error("Error: mlx_new_window() failed.");
	load_textures(game);
	render_game(game);
	mlx_hook(game->win, EVENT_KEY_PRESS, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, EVENT_DESTROY, 1L << 17, close_game, game);
}

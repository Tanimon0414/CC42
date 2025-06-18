/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:58:04 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/18 16:58:24 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*get_tile_image(t_game *game, char tile_char)
{
	if (tile_char == '1')
		return (game->img.wall);
	if (tile_char == 'P')
		return (game->img.player);
	if (tile_char == 'C')
		return (game->img.collectible);
	if (tile_char == 'E')
		return (game->img.exit);
	return (game->img.floor);
}

static void	draw_tile(t_game *game, int y, int x)
{
	char	tile_char;
	void	*img_to_draw;

	tile_char = game->map->grid[y][x];
	img_to_draw = get_tile_image(game, tile_char);
	mlx_put_image_to_window(game->mlx, game->win, img_to_draw, x * TILE_SIZE, y
		* TILE_SIZE);
}

int	render_game(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			/* 床を先に描画してからオブジェクトを描画すると透過が綺麗にいく */
			mlx_put_image_to_window(game->mlx, game->win, game->img.floor, x
				* TILE_SIZE, y * TILE_SIZE);
			draw_tile(game, y, x);
			x++;
		}
		y++;
	}
	return (0);
}

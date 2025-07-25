/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:00:33 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/20 14:47:38 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_player_state(t_game *game, int new_x, int new_y,
		char dest_tile)
{
	int	old_x;
	int	old_y;

	old_x = game->map->p_x;
	old_y = game->map->p_y;
	game->map->grid[old_y][old_x] = game->tile_under_player;
	if (dest_tile == 'C')
	{
		game->map->c_count--;
		game->tile_under_player = '0';
	}
	else
		game->tile_under_player = dest_tile;
	game->map->grid[new_y][new_x] = 'P';
	game->map->p_x = new_x;
	game->map->p_y = new_y;
}

static void	move_player(t_game *game, int new_x, int new_y)
{
	char	dest_tile;

	dest_tile = game->map->grid[new_y][new_x];
	if (dest_tile == '1')
		return ;
	if (dest_tile == 'E' && game->map->c_count == 0)
	{
		game->move_count++;
		ft_printf("Move count: %d\n", game->move_count);
		ft_printf("YOU WIN!\n");
		close_game(game);
	}
	update_player_state(game, new_x, new_y, dest_tile);
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	render_game(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		move_player(game, game->map->p_x, game->map->p_y - 1);
	else if (keycode == KEY_A)
		move_player(game, game->map->p_x - 1, game->map->p_y);
	else if (keycode == KEY_S)
		move_player(game, game->map->p_x, game->map->p_y + 1);
	else if (keycode == KEY_D)
		move_player(game, game->map->p_x + 1, game->map->p_y);
	return (0);
}

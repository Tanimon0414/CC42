/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:00:57 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/18 16:56:22 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;

	map = parse_map(argc, argv);
	init_game(&game, map);
	start_mlx(&game);
	mlx_loop(game.mlx);
	return (0);
}

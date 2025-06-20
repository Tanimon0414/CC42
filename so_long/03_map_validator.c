/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:49:20 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/20 16:35:23 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * 新しいヘルパー関数：1文字を処理し、種類に応じてカウンターを増やす
 */
static void	process_char(t_map *map, int y, int x)
{
	char	c;

	c = map->grid[y][x];
	if (c == 'P')
	{
		map->p_count++;
		map->p_x = x;
		map->p_y = y;
	}
	else if (c == 'C')
		map->c_count++;
	else if (c == 'E')
		map->e_count++;
	else if (c != '0' && c != '1')
		exit_with_error("Error: Invalid character in map.");
}

/*
 * ヘルパー関数：マップを走査し、文字の処理をprocess_charに委譲する
 */
static void	count_and_validate_chars(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		if ((int)ft_strlen(map->grid[y]) != map->width)
			exit_with_error("Error: Map is not rectangular.");
		x = -1;
		while (++x < map->width)
			process_char(map, y, x);
	}
}

/*
 * 4&5&7. マップが長方形であること、構成文字が正しいこと、
 * P, E, Cの数がルール通りであることを検証する
 */
void	check_map_components(t_map *map)
{
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
	if (map->height == 0)
		exit_with_error("Error: Map is empty.");
	map->width = ft_strlen(map->grid[0]);
	map->p_count = 0;
	map->c_count = 0;
	map->e_count = 0;
	count_and_validate_chars(map);
	if (map->p_count != 1 || map->e_count != 1 || map->c_count < 1)
		exit_with_error("Error: Invalid number of players,etc");
}

/*
 * 6. マップが壁で囲まれているか検証する
 */
void	check_walls(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->width)
	{
		if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1')
			exit_with_error("Error: Map is not enclosed by walls.");
	}
	i = -1;
	while (++i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			exit_with_error("Error: Map is not enclosed by walls.");
	}
}

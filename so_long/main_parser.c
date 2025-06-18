/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:46:27 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/18 15:40:54 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "so_long.h"

/*
 * 1. 引数の数をチェックし、ファイルが.ber拡張子を持つか検証する
 */
static void	check_arguments(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		exit_with_error("Error: Invalid number of arguments.\nUsage: ./so_long <map.ber>");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
		exit_with_error("Error: Map file must have a .ber extension.");
}

/*
 * 2. マップファイルを読み込み、char**の2次元配列に格納する
 * (get_next_lineとlibftのft_split, ft_strjoinを想定)
 */
static char	**read_map_file(char *filename)
{
	int		fd;
	char	*line;
	char	*full_map_str;
	char	**map_grid;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: Could not open map file.");
	full_map_str = ft_strdup("");
	while ((line = get_next_line(fd)))
	{
		temp = ft_strjoin(full_map_str, line);
		free(full_map_str);
		free(line);
		full_map_str = temp;
	}
	close(fd);
	map_grid = ft_split(full_map_str, '\n');
	free(full_map_str);
	if (!map_grid || !map_grid[0])
		exit_with_error("Error: Map is empty or failed to read.");
	return (map_grid);
}

/*
 * 3. マップ全体の検証を呼び出す
 */
static void	validate_map(t_map *map)
{
	check_map_components(map);
	check_walls(map);
	check_path(map);
}

t_map	*parse_map(int argc, char **argv)
{
	t_map	*map_data;

	check_arguments(argc, argv);
	map_data = (t_map *)malloc(sizeof(t_map));
	if (!map_data)
		exit_with_error("Error: Memory allocation failed.");
	map_data->grid = read_map_file(argv[1]);
	validate_map(map_data);
	return (map_data);
}

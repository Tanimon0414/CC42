/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:46:27 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/20 13:59:35 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * 1. 引数の数をチェックし、ファイルが.ber拡張子を持つか検証する
 */
static void	check_arguments(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		exit_with_error("Error: Invalid number of arguments.\n");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
		exit_with_error("Error: Map file must have a .ber extension.");
}

/*
 * ヘルパー関数: ファイルディスクリプタから全ての行を読み込み、
 * 一つの結合された文字列として返す。
 */
static char	*read_file_content(int fd)
{
	char	*line;
	char	*full_str;
	char	*temp;

	full_str = ft_strdup("");
	if (!full_str)
		exit_with_error("Error: Memory allocation failed.");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strjoin(full_str, line);
		free(full_str);
		free(line);
		if (!temp)
			exit_with_error("Error: ft_strjoin failed.");
		full_str = temp;
	}
	return (full_str);
}

/*
 * 2. マップファイルを読み込み、char**の2次元配列に格納する。
 * 25行以内に収まるようにリファクタリング済み。
 */
static char	**read_map_file(char *filename)
{
	int		fd;
	char	*full_map_str;
	char	**map_grid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: Could not open map file.");
	full_map_str = read_file_content(fd);
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

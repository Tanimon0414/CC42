/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:46:27 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/25 16:50:26 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_arguments(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		exit_with_error("Error: Invalid number of arguments.\n");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
		exit_with_error("Error: Map file must have a .ber extension.");
}

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

static void	validate_raw_map_str(char *full_map_str)
{
	size_t	len;

	if (ft_strnstr(full_map_str, "\n\n", ft_strlen(full_map_str)))
	{
		free(full_map_str);
		exit_with_error("Error: Map contains one or more empty lines.");
	}
	len = ft_strlen(full_map_str);
	if (full_map_str[0] == '\n' || full_map_str[len - 1] == '\n')
	{
		free(full_map_str);
		exit_with_error("Error: Map has leading or trailing empty lines.");
	}
}

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
	if (!*full_map_str)
	{
		free(full_map_str);
		exit_with_error("Error: Map file is empty.");
	}
	validate_raw_map_str(full_map_str);
	map_grid = ft_split(full_map_str, '\n');
	free(full_map_str);
	return (map_grid);
}

t_map	*parse_map(int argc, char **argv)
{
	t_map	*map_data;
	char	**grid_tmp;

	check_arguments(argc, argv);
	grid_tmp = read_map_file(argv[1]);
	map_data = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map_data)
	{
		free_grid(grid_tmp);
		exit_with_error("Error: Memory allocation failed.");
	}
	map_data->grid = grid_tmp;
	if (!map_data->grid || !map_data->grid[0])
	{
		free_map(map_data);
		exit_with_error("Error: Map is empty or failed to read.");
	}
	validate_map(map_data);
	return (map_data);
}

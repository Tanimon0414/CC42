/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_path_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:51:12 by atanimot          #+#    #+#             */
/*   Updated: 2025/07/20 18:41:55 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_directions	*get_directions(void)
{
	static t_directions	dirs = {{0, 0, 1, -1}, {1, -1, 0, 0}};

	return (&dirs);
}

static char	**create_and_init_visited_map(int height, int width)
{
	char	**visited;
	int		i;
	int		j;

	visited = (char **)malloc(sizeof(char *) * (height + 1));
	if (!visited)
		exit_with_error("Error: Visited map allocation failed.");
	i = -1;
	while (++i < height)
	{
		visited[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!visited[i])
		{
			free_grid(visited);
			exit_with_error("Error: Visited map row allocation failed.");
		}
		j = -1;
		while (++j < width)
			visited[i][j] = '0';
		visited[i][j] = '\0';
	}
	visited[i] = NULL;
	return (visited);
}

static void	init_bfs_data(t_bfs *bfs, t_map *map)
{
	bfs->found_c = 0;
	bfs->found_e = 0;
	bfs->visited = create_and_init_visited_map(map->height, map->width);
	bfs->queue = create_queue(map->width * map->height);
	bfs->visited[map->p_y][map->p_x] = '1';
	enqueue(bfs->queue, map->p_x, map->p_y);
}

static void	explore_neighbors(t_bfs *bfs, t_map *map, t_point curr)
{
	int				i;
	t_point			next;
	t_directions	*dirs;

	dirs = get_directions();
	i = -1;
	while (++i < 4)
	{
		next.x = curr.x + dirs->dx[i];
		next.y = curr.y + dirs->dy[i];
		if (next.y < 0 || next.y >= map->height || next.x < 0
			|| next.x >= map->width)
			continue ;
		if (map->grid[next.y][next.x] != '1'
			&& bfs->visited[next.y][next.x] == '0')
		{
			bfs->visited[next.y][next.x] = '1';
			enqueue(bfs->queue, next.x, next.y);
		}
	}
}

void	check_path(t_map *map)
{
	t_bfs	bfs;
	t_point	curr;

	init_bfs_data(&bfs, map);
	while (bfs.queue->front < bfs.queue->rear)
	{
		curr = dequeue(bfs.queue);
		if (map->grid[curr.y][curr.x] == 'C')
			bfs.found_c++;
		if (map->grid[curr.y][curr.x] == 'E')
			bfs.found_e = 1;
		explore_neighbors(&bfs, map, curr);
	}
	free(bfs.queue->points);
	free(bfs.queue);
	free_grid(bfs.visited);
	if (!bfs.found_e || bfs.found_c != map->c_count)
	{
		free_map(map);
		exit_with_error("Error: No valid path found.");
	}
}

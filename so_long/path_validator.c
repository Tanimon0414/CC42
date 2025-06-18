/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:02:46 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/18 15:23:32 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_queue
{
	t_point		*points;
	int			front;
	int			rear;
	int			capacity;
}				t_queue;

// --- BFSのためのヘルパー関数 ---
static t_queue	*create_queue(int capacity)
{
	t_queue	*q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (!q)
		exit_with_error("Error: Queue allocation failed.");
	q->points = (t_point *)malloc(sizeof(t_point) * capacity);
	if (!q->points)
	{
		free(q);
		exit_with_error("Error: Queue points allocation failed.");
	}
	q->front = 0;
	q->rear = 0;
	q->capacity = capacity;
	return (q);
}
static void	enqueue(t_queue *q, int x, int y)
{
	if (q->rear < q->capacity)
	{
		q->points[q->rear].x = x;
		q->points[q->rear].y = y;
		q->rear++;
	}
}

static t_point	dequeue(t_queue *q)
{
	t_point	p;

	p = q->points[q->front];
	q->front++;
	return (p);
}

/*
 * 8. 有効な経路が存在するかBFSで検証する
 */
static char	**create_visited_map(int height, int width)
{
	char	**visited;
	int		i;
	int		j;

	visited = (char **)malloc(sizeof(char *) * (height + 1));
	if (!visited)
		exit_with_error("Error: Visited map allocation failed.");
	i = 0;
	while (i < height)
	{
		visited[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!visited[i])
		{
			free_grid(visited);
			exit_with_error("Error: Visited map row allocation failed.");
		}
		j = 0;
		while (j < width)
			visited[i][j++] = '0';
		visited[i][j] = '\0';
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

void	check_path(t_map *map)
{
	t_queue	*queue;
	char	**visited;
	int		found_c;
	int		found_e;
	t_point	curr;
	int		i;
	int		dx[4] = {0, 0, 1, -1};
	int		dy[4] = {1, -1, 0, 0};
	int		nx;
	int		ny;

	found_c = 0;
	found_e = 0;
	visited = create_visited_map(map->height, map->width);
	queue = create_queue(map->width * map->height);
	enqueue(queue, map->p_x, map->p_y);
	visited[map->p_y][map->p_x] = '1';
	while (queue->front < queue->rear)
	{
		curr = dequeue(queue);
		if (map->grid[curr.y][curr.x] == 'C')
			found_c++;
		if (map->grid[curr.y][curr.x] == 'E')
			found_e = 1;
		i = -1;
		while (++i < 4)
		{
			nx = curr.x + dx[i];
			ny = curr.y + dy[i];
			if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height
				&& map->grid[ny][nx] != '1' && visited[ny][nx] == '0')
			{
				visited[ny][nx] = '1';
				enqueue(queue, nx, ny);
			}
		}
	}
	free(queue->points);
	free(queue);
	free_grid(visited);
	if (!found_e || found_c != map->c_count)
		exit_with_error("Error: Invalid path. Not all items or the exit are reachable.");
}

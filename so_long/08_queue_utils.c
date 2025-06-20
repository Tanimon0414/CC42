/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_queue_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:50:23 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/20 13:50:35 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_queue	*create_queue(int capacity)
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

void	enqueue(t_queue *q, int x, int y)
{
	if (q->rear < q->capacity)
	{
		q->points[q->rear].x = x;
		q->points[q->rear].y = y;
		q->rear++;
	}
}

t_point	dequeue(t_queue *q)
{
	t_point	p;

	p.x = -1;
	p.y = -1;
	if (q->front < q->rear)
	{
		p = q->points[q->front];
		q->front++;
	}
	return (p);
}

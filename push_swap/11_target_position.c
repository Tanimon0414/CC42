/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_target_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:04:05 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:47:29 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_best_fit_in_a(t_stack *a, int idx)
{
	t_node	*cur;
	int		i;
	int		target_pos;
	int		diff;

	cur = a->top;
	i = 0;
	diff = INT_MAX;
	target_pos = -1;
	while (i < a->size)
	{
		if (cur->index > idx && cur->index - idx < diff)
		{
			diff = cur->index - idx;
			target_pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (target_pos);
}

static int	find_max_pos(t_stack *stack)
{
	t_node	*cur;
	int		i;
	int		max_idx;
	int		max_pos;

	cur = stack->top;
	i = 0;
	max_idx = INT_MIN;
	max_pos = 0;
	while (i < stack->size)
	{
		if (cur->index > max_idx)
		{
			max_idx = cur->index;
			max_pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (max_pos);
}

static int	find_best_fit_in_b(t_stack *b, int idx)
{
	t_node	*cur;
	int		i;
	int		target_pos;
	int		diff;

	cur = b->top;
	i = 0;
	diff = INT_MAX;
	target_pos = -1;
	while (i < b->size)
	{
		if (cur->index < idx && idx - cur->index < diff)
		{
			diff = idx - cur->index;
			target_pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (target_pos);
}

int	target_pos_in_a(t_stack *a, int idx)
{
	int	target_pos;

	if (a->size == 0)
		return (0);
	target_pos = find_best_fit_in_a(a, idx);
	if (target_pos != -1)
		return (target_pos);
	return (find_min_pos(a));
}

int	target_pos_in_b(t_stack *b, int idx)
{
	int	target_pos;

	if (b->size == 0)
		return (0);
	target_pos = find_best_fit_in_b(b, idx);
	if (target_pos != -1)
		return (target_pos);
	return (find_max_pos(b));
}

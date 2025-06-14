/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_cost_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:06:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 17:39:48 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	calc_cost_for_node_toa(t_node *cur, t_stack *a, t_stack *b, int pos)
{
	int	cost_a;
	int	cost_b;
	int	pos_a;
	int	common;

	cost_b = rotation_cost(b->size, pos);
	pos_a = target_pos_in_a(a, cur->index);
	cost_a = rotation_cost(a->size, pos_a);
	common = save_cost(cost_a, cost_b, cur);
	set_commands(cost_a, cost_b, common, cur);
}

static void	calc_cost_for_node_tob(t_node *cur, t_stack *a, t_stack *b, int pos)
{
	int	cost_a;
	int	cost_b;
	int	pos_b;
	int	common;

	cost_a = rotation_cost(a->size, pos);
	pos_b = target_pos_in_b(b, cur->index);
	cost_b = rotation_cost(b->size, pos_b);
	common = save_cost(cost_a, cost_b, cur);
	set_commands(cost_a, cost_b, common, cur);
}

void	count_commands_toa(t_stack *a, t_stack *b)
{
	t_node	*cur;
	int		i;

	cur = b->top;
	i = 0;
	while (i < b->size)
	{
		calc_cost_for_node_toa(cur, a, b, i);
		cur = cur->next;
		i++;
	}
}

void	count_commands_tob(t_stack *a, t_stack *b)
{
	t_node	*cur;
	int		i;

	cur = a->top;
	i = 0;
	while (i < a->size)
	{
		calc_cost_for_node_tob(cur, a, b, i);
		cur = cur->next;
		i++;
	}
}

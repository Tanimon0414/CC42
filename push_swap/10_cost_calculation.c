/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_cost_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:06:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 18:57:13 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*get_node_at_pos(t_stack *stack, int pos)
{
	t_node	*cur;
	int		i;

	cur = stack->top;
	i = 0;
	while (i < pos)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
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
	t_node	*target_node;
	int		pos_in_b;
	int		cost_a;
	int		cost_b;
	int		common;

	if (b->size == 0)
		return ;
	pos_in_b = find_max_pos(b);
	target_node = get_node_at_pos(b, pos_in_b);
	cost_b = rotation_cost(b->size, pos_in_b);
	cost_a = rotation_cost(a->size, target_pos_in_a(a, target_node->index));
	common = save_cost(cost_a, cost_b, target_node);
	set_commands(cost_a, cost_b, common, target_node);
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

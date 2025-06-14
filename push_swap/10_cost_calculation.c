/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_cost_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:06:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:47:03 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_commands(int cost_a, int cost_b, int common, t_node *cur)
{
	if (cost_a >= 0)
		cur->command.ra = cost_a;
	else
		cur->command.rra = -cost_a;
	if (cost_b >= 0)
		cur->command.rb = cost_b;
	else
		cur->command.rrb = -cost_b;
	if (cur->command.rr > 0)
	{
		cur->command.ra -= common;
		cur->command.rb -= common;
	}
	else if (cur->command.rrr > 0)
	{
		cur->command.rra -= common;
		cur->command.rrb -= common;
	}
	cur->command.all = cur->command.ra + cur->command.rra + cur->command.rb
		+ cur->command.rrb + cur->command.rr + cur->command.rrr + 1;
}

static int	save_cost(int cost_a, int cost_b, t_node *cur)
{
	int	common;
	int	abs_a;
	int	abs_b;

	common = 0;
	if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
	{
		abs_a = ft_abs(cost_a);
		abs_b = ft_abs(cost_b);
		common = ft_min(abs_a, abs_b);
		if (cost_a >= 0)
			cur->command.rr = common;
		else
			cur->command.rrr = common;
	}
	return (common);
}

void	count_commands_toa(t_stack *a, t_stack *b)
{
	int		i;
	int		common;
	int		cost_b;
	int		pos_a;
	int		cost_a;
	t_node	*cur;

	cur = b->top;
	i = 0;
	while (i < b->size)
	{
		cost_b = rotation_cost(b->size, i);
		pos_a = target_pos_in_a(a, cur->index);
		cost_a = rotation_cost(a->size, pos_a);
		common = save_cost(cost_a, cost_b, cur);
		set_commands(cost_a, cost_b, common, cur);
		cur = cur->next;
		i++;
	}
}

void	count_commands_tob(t_stack *a, t_stack *b)
{
	t_node	*cur;
	int		i;
	int		cost_a;
	int		pos_b;
	int		cost_b;
	int		common;

	cur = a->top;
	i = 0;
	while (i < a->size)
	{
		cost_a = rotation_cost(a->size, i);
		pos_b = target_pos_in_b(b, cur->index);
		cost_b = rotation_cost(b->size, pos_b);
		common = save_cost(cost_a, cost_b, cur);
		set_commands(cost_a, cost_b, common, cur);
		cur = cur->next;
		i++;
	}
}

int	rotation_cost(int size, int pos)
{
	if (pos <= size / 2)
		return (pos);
	else
		return (pos - size);
}

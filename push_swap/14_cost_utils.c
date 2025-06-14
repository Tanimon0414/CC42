/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_cost_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:38:12 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 17:42:33 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_commands(int cost_a, int cost_b, int common, t_node *cur)
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

int	save_cost(int cost_a, int cost_b, t_node *cur)
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

int	rotation_cost(int size, int pos)
{
	if (pos <= size / 2)
		return (pos);
	else
		return (pos - size);
}

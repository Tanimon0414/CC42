/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_sort_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:45:43 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 16:32:13 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_node_tob(int idx, t_stack *a, t_stack *b)
{
	t_node	*cur;
	int		i;

	cur = a->top;
	i = 0;
	while (i < idx)
	{
		cur = cur->next;
		i++;
	}
	exec_rot(a, b, &cur->command);
	pb(a, b, 1);
}

static void	move_node_toa(int idx, t_stack *b, t_stack *a)
{
	t_node	*cur;
	int		i;

	cur = b->top;
	i = 0;
	while (i < idx)
	{
		cur = cur->next;
		i++;
	}
	exec_rot_rev(a, b, &cur->command);
	pa(a, b, 1);
}

static void	exec_rot(t_stack *a, t_stack *b, t_command *c)
{
	while (c->rr-- > 0)
		rr(a, b, 1);
	while (c->rrr-- > 0)
		rrr(a, b, 1);
	while (c->ra-- > 0)
		ra(a, 1);
	while (c->rra-- > 0)
		rra(a, 1);
	while (c->rb-- > 0)
		rb(b, 1);
	while (c->rrb-- > 0)
		rrb(b, 1);
}

static void	exec_rot_rev(t_stack *a, t_stack *b, t_command *c)
{
	while (c->rr--)
		rr(a, b, 1);
	while (c->rrr--)
		rrr(a, b, 1);
	while (c->rb--)
		rb(b, 1);
	while (c->rrb--)
		rrb(b, 1);
	while (c->ra--)
		ra(a, 1);
	while (c->rra--)
		rra(a, 1);
}

void	sort_stacks(t_stack *a, t_stack *b)
{
	int	move_idx;

	if (a->size <= 5)
	{
		sort_stacks_small(a, b);
		return ;
	}
	pb(a, b, 1);
	pb(a, b, 1);
	while (a->size > 3)
	{
		init_commands(a);
		count_commands_tob(a, b);
		move_idx = search_min(a);
		move_node_tob(move_idx, a, b);
	}
	sort_three(a);
	while (b->size > 0)
	{
		init_commands(b);
		count_commands_toa(a, b);
		move_idx = search_min(b);
		move_node_toa(move_idx, b, a);
	}
	align_min_on_top(a);
}

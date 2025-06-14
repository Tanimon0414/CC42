/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:52:54 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:46:50 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ra_or_rra(t_stack *stack_a, int pos)
{
	int	j;

	if (pos <= stack_a->size / 2)
	{
		j = 0;
		while (j < pos)
		{
			ra(stack_a, 1);
			j++;
		}
	}
	else
	{
		j = pos;
		while (j < stack_a->size)
		{
			rra(stack_a, 1);
			j++;
		}
	}
}

void	sort_stacks_small(t_stack *stack_a, t_stack *stack_b)
{
	int	pos;

	if (stack_a->size == 2 && !check_sorted(stack_a))
		sa(stack_a, 1);
	else if (stack_a->size == 3)
		sort_three(stack_a);
	else if (stack_a->size <= 5)
	{
		while (stack_a->size > 3)
		{
			pos = find_min_pos(stack_a);
			ra_or_rra(stack_a, pos);
			pb(stack_a, stack_b, 1);
		}
		sort_three(stack_a);
		while (stack_b->size > 0)
			pa(stack_a, stack_b, 1);
	}
}

void	sort_three(t_stack *a)
{
	int	x;
	int	y;
	int	z;

	x = a->top->data;
	y = a->top->next->data;
	z = a->top->prev->data;
	if (x > y && y < z && x < z)
		sa(a, 1);
	else if (x > y && y > z)
	{
		sa(a, 1);
		rra(a, 1);
	}
	else if (x > y && y < z && x > z)
		ra(a, 1);
	else if (x < y && y > z && x < z)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (x < y && y > z && x > z)
		rra(a, 1);
}

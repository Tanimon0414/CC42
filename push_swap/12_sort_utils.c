/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:22:01 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:06:27 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	align_min_on_top(t_stack *a)
{
	int	pos;
	int	i;

	pos = find_min_pos(a);
	if (pos <= a->size / 2)
	{
		i = 0;
		while (i < pos)
		{
			ra(a, 1);
			i++;
		}
	}
	else
	{
		i = pos;
		while (i < a->size)
		{
			rra(a, 1);
			i++;
		}
	}
}

int	find_min_pos(t_stack *s)
{
	t_node	*cur;
	int		min_idx;
	int		min_pos;
	int		i;

	cur = s->top;
	min_idx = INT_MAX;
	min_pos = 0;
	i = 0;
	while (i < s->size)
	{
		if (cur->index < min_idx)
		{
			min_idx = cur->index;
			min_pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (min_pos);
}

int	search_min(t_stack *a)
{
	t_node	*cur;
	int		i;
	int		best_idx;
	int		best_cost;

	cur = a->top;
	i = 0;
	best_idx = 0;
	best_cost = INT_MAX;
	while (i < a->size)
	{
		if (cur->command.all <= i + 2)
			return (i);
		if (cur->command.all < best_cost)
		{
			best_cost = cur->command.all;
			best_idx = i;
		}
		cur = cur->next;
		i++;
	}
	return (best_idx);
}

int	check_sorted(t_stack *stack)
{
	t_node	*current;
	int		i;

	current = stack->top;
	i = 0;
	while (i < stack->size)
	{
		if (current->index != i)
			break ;
		current = current->next;
		i++;
	}
	if (i == stack->size)
		return (1);
	return (0);
}

void	init_commands(t_stack *stack_a)
{
	t_node	*cur;
	int		i;

	cur = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		ft_bzero(&cur->command, sizeof(t_command));
		cur = cur->next;
		i++;
	}
}

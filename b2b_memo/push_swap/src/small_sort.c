/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 06:04:40 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/21 10:01:17 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	sa_and_ra(t_stack **stack)
{
	sa(stack, 1);
	ra(stack, 1);
}

static void	sa_and_rra(t_stack **stack)
{
	sa(stack, 1);
	rra(stack, 1);
}

void	sort_3_args(t_stack **stack)
{
	int		min;
	int		next_min;
	t_stack	*head;

	if (is_stack_sorted(stack))
		return ;
	head = *stack;
	min = place_of_min_index(stack, -1);
	next_min = place_of_min_index(stack, min);
	if (head->i == min)
		sa_and_ra(stack);
	else if (head->i == next_min)
	{
		if (head->next->i == min)
			sa(stack, 1);
		else
			rra(stack, 1);
	}
	else
	{
		if (head->next->i == min)
			ra(stack, 1);
		else
			sa_and_rra(stack);
	}
}

static void	sort_5_args_init(t_stack **a, t_stack **b, int min, int max)
{
	t_stack	*last_a;

	last_a = *a;
	while (last_a->next)
		last_a = last_a->next;
	if ((last_a->i == min) || (last_a->i == max))
	{
		rra(a, 1);
		pb(a, b, 1);
	}
}

void	sort_5_args(t_stack **a, t_stack **b)
{
	int		min;
	int		max;

	min = place_of_min_index(a, -1);
	max = place_of_max_index(a, -1);
	sort_5_args_init(a, b, min, max);
	sort_5_args_init(a, b, min, max);
	while (stack_size(*b) < 2)
	{
		if (((*a)->i == min) || ((*a)->i == max))
			pb(a, b, 1);
		else
			ra(a, 1);
	}
	sort_3_args(a);
	while (stack_size(*b) > 0)
	{
		pa(a, b, 1);
		if ((*a)->i > (*a)->next->i)
			ra(a, 1);
	}
}

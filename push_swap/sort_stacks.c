/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:22:01 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/08 20:48:21 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_node(int move_index, t_stack *stack_a, t_stack *stack_b)
{
	t_node	*current_a;
}

void	search_goal(t_node *current_a, t_stack *stack_b)
{
}

int	count_command(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*current_a;

	current_a = stack_a->top;
	while (current_a != NULL)
	{
		search_goal(current_a, stack_b);
	}
}

void	set_command(t_stack *stack_a, t_stack *stack_b)
{
}

void	sort_stacks_small(t_stack *stack_a, t_stack *stack_b)
{
}

void	sort_stacks(t_stack *stack_a, t_stack *stack_b)
{
	int	move_index;

	int pn; // process number
	if (stack_a->size < 5)
		sort_stacks_small(stack_a, stack_b);
	while (stack_a->size > 3) // 選定→pbするループ
	{
		set_command(stack_a, stack_b);
		move_index = count_command(stack_a, stack_b); //最終的に動かすaのノードのインデックスを返す
		move_node(move_index, stack_a, stack_b);
	}
}

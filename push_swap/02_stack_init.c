/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_stack_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:20:35 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:45:44 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_index_all(t_stack *stack)
{
	t_node	*current;
	int		j;

	current = stack->top;
	j = 0;
	while (j < stack->size)
	{
		current->index = -1;
		current = current->next;
		j++;
	}
	return ;
}

static int	search_min_data(t_stack *stack)
{
	int		min;
	int		j;
	t_node	*current;

	min = INT_MAX;
	j = 0;
	current = stack->top;
	while (j < stack->size)
	{
		if (min > current->data && current->index == -1)
			min = current->data;
		current = current->next;
		j++;
	}
	return (min);
}

static void	put_index(t_stack *stack, int i, int min)
{
	int		j;
	t_node	*current;

	j = 0;
	current = stack->top;
	while (j < stack->size)
	{
		if (current->data == min)
		{
			current->index = i;
			break ;
		}
		current = current->next;
		j++;
	}
	return ;
}

void	initialize_stacks(t_stack **stack_a_ptr, t_stack **stack_b_ptr)
{
	*stack_a_ptr = (t_stack *)malloc(sizeof(t_stack));
	if (!(*stack_a_ptr))
		print_error_and_exit();
	(*stack_a_ptr)->top = NULL;
	(*stack_a_ptr)->size = 0;
	*stack_b_ptr = (t_stack *)malloc(sizeof(t_stack));
	if (!(*stack_b_ptr))
	{
		clear_stack(stack_a_ptr);
		print_error_and_exit();
	}
	(*stack_b_ptr)->top = NULL;
	(*stack_b_ptr)->size = 0;
}

void	set_index(t_stack *stack_a)
{
	int	i;
	int	min;

	if (!stack_a || stack_a->top == NULL)
		return ;
	i = 0;
	set_index_all(stack_a);
	while (i < stack_a->size)
	{
		min = search_min_data(stack_a);
		put_index(stack_a, i, min);
		i++;
	}
	return ;
}

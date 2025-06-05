/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:20:35 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 16:17:39 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	dup_check(t_stack *stack_a_ptr, t_node *new_node)
{
	t_node	*current_check_node;

	current_check_node = stack_a_ptr->top;
	while (current_check_node != NULL)
	{
		if (current_check_node->data == new_node->data)
			return (0);
		current_check_node = current_check_node->next;
	}
	return (1);
}

static t_node	*create_and_init_node(long num_val, t_stack **sa_ptr,
		t_stack **sb_ptr)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		stack_error(sa_ptr, sb_ptr);
	node->data = (int)num_val;
	node->index = 0;
	node->next = node;
	node->prev = node;
	return (node);
}

void	check_and_set(int argc, char **argv, t_stack **stack_a_ptr,
		t_stack **stack_b_ptr)
{
	int		i;
	long	num_val;
	t_node	*new_node;

	i = 1;
	while (i < argc)
	{
		num_val = ft_atol_strict(argv[i]);
		if (num_val > INT_MAX || num_val < INT_MIN)
			stack_error(stack_a_ptr, stack_b_ptr);
		new_node = create_and_init_node(num_val, stack_a_ptr, stack_b_ptr);
		if (!dup_check(*stack_a_ptr, new_node))
		{
			free(new_node);
			stack_error(stack_a_ptr, stack_b_ptr);
		}
		add_node_to_back(*stack_a_ptr, new_node);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:08:39 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 11:44:01 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error_and_exit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	clear_stack(t_stack **stack_ptr)
{
	t_node	*current;
	t_node	*next_node;

	if (stack_ptr == NULL || *stack_ptr == NULL)
		return ;
	current = (*stack_ptr)->top;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	free(*stack_ptr);
	*stack_ptr = NULL;
}

void	stack_error(t_stack **stack_a_ptr, t_stack **stack_b_ptr)
{
	clear_stack(stack_a_ptr);
	clear_stack(stack_b_ptr);
	print_error_and_exit();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:20 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:22:59 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	t_node	*head_b;

	head_b = pop_node_from_front(stack_b);
	if (!head_b)
		return ;
	add_node_to_front(stack_a, head_b);
	if (print_op)
		ft_printf("pa\n");
	return ;
}

void	pb(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	t_node	*head_a;

	head_a = pop_node_from_front(stack_a);
	if (!head_a)
		return ;
	add_node_to_front(stack_b, head_a);
	if (print_op)
		ft_printf("pb\n");
	return ;
}

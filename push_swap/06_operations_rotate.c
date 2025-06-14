/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:34:23 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 14:31:29 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack *stack, int print_op)
{
	if (!stack || !stack->top || stack->size < 2)
		return ;
	stack->top = stack->top->next;
	if (print_op)
		ft_printf("ra\n");
	return ;
}

void	rb(t_stack *stack, int print_op)
{
	if (!stack || !stack->top || stack->size < 2)
		return ;
	stack->top = stack->top->next;
	if (print_op)
		ft_printf("rb\n");
	return ;
}

void	rr(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	if (print_op)
		ft_printf("rr\n");
	return ;
}

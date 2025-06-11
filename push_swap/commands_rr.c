/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_rr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:34:40 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/06 14:27:15 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *stack, int print_op)
{
	if (!stack || !stack->top || stack->size < 2)
		return ;
	stack->top = stack->top->prev;
	if (print_op)
		ft_printf("rra\n");
	return ;
}

void	rrb(t_stack *stack, int print_op)
{
	if (!stack || !stack->top || stack->size < 2)
		return ;
	stack->top = stack->top->prev;
	if (print_op)
		ft_printf("rrb\n");
	return ;
}

void	rrr(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	if (print_op)
		ft_printf("rrr\n");
	return ;
}

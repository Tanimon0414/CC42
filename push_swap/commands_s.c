/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:45:43 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/06 14:44:07 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	elswap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;
	t_node	*last;

	first = stack->top;
	second = first->next;
	last = first->prev;
	third = second->next;
	stack->top = second;
	second->prev = last;
	second->next = first;
	first->prev = second;
	first->next = third;
	last->next = second;
	third->prev = first;
	return ;
}

void	sa(t_stack *stack_a, int print_op)
{
	t_node	*first;
	t_node	*second;

	if (!stack_a || !stack_a->top || !stack_a->top->next || stack_a->size < 2)
		return ;
	first = stack_a->top;
	second = first->next;
	if (stack_a->size == 2)
		stack_a->top = second;
	else
		elswap(stack_a);
	if (print_op)
		ft_printf("sa\n");
	return ;
}

void	sb(t_stack *stack_b, int print_op)
{
	t_node	*first;
	t_node	*second;

	if (!stack_b || !stack_b->top || !stack_b->top->next || stack_b->size < 2)
		return ;
	first = stack_b->top;
	second = first->next;
	if (stack_b->size == 2)
		stack_b->top = second;
	else
		elswap(stack_b);
	if (print_op)
		ft_printf("sb\n");
	return ;
}

void	ss(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	if (print_op)
		ft_printf("ss\n");
	return ;
}

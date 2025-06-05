/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:45:43 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 17:58:14 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *stack_a, int print_op)
{
	t_node *first;
	t_node *second;
	t_node *tail;
	if (!stack_a || !stack_a->top || !stack_a->top->next || stack_a->size < 2)
		return ;
	first = stack_a->top;
	second = first->next;
	tail = first->prev;
	if ()

		if (print_op)
		{
			// ft_printf("sa\n");
			printf("sa\n");
		}
}
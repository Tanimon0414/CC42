/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:20 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/06 18:52:57 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	}
	return ;
}

static int	search_min(t_stack *stack)
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
		min = search_min(stack_a);
		put_index(stack_a, i, min);
		i++;
	}
	return ;
}

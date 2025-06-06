/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:25:33 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/06 18:37:00 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	debug_print_stack_values(t_stack *stack, const char *stack_name)
{
	t_node	*current;
	int		i;

	if (stack_name == NULL)
		printf("Stack name is NULL.\n");
	else
		printf("%s: ", stack_name);
	if (!stack)
	{
		printf("(null stack)\n");
		return ;
	}
	printf("(size: %d) ", stack->size);
	if (stack->top == NULL)
	{
		printf("(empty)\n");
		return ;
	}
	current = stack->top;
	i = 0;
	while (i < stack->size)
	{
		printf("%d", current->data);
		if (i < stack->size - 1)
		{
			printf(" -> ");
		}
		current = current->next;
		i++;
	}
	printf("\n");
}

void	debug_print_stack_index(t_stack *stack, const char *stack_name)
{
	t_node	*current;
	int		i;

	if (stack_name == NULL)
		printf("Stack name is NULL.\n");
	else
		printf("%s: ", stack_name);
	if (!stack)
	{
		printf("(null stack)\n");
		return ;
	}
	printf("(size: %d) ", stack->size);
	if (stack->top == NULL)
	{
		printf("(empty)\n");
		return ;
	}
	current = stack->top;
	i = 0;
	while (i < stack->size)
	{
		printf("%d", current->index);
		if (i < stack->size - 1)
		{
			printf(" -> ");
		}
		current = current->next;
		i++;
	}
	printf("\n");
}

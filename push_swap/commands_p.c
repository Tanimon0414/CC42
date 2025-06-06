/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:17:42 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 20:53:27 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_node_to_back(t_stack *stack, t_node *new_node)
{
	t_node	*head;
	t_node	*tail;

	if (!stack || !new_node)
		return ;
	if (stack->top == NULL)
	{
		stack->top = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		head = stack->top;
		tail = head->prev;
		new_node->prev = tail;
		new_node->next = head;
		tail->next = new_node;
		head->prev = new_node;
	}
	stack->size++;
}

t_node	*pop_node_from_front(t_stack *stack)
{
	t_node	*popped_node;
	t_node	*head;
	t_node	*tail;

	if (!stack || stack->top == NULL)
		return (NULL);
	popped_node = stack->top;
	head = stack->top;
	if (stack->size == 1)
		stack->top = NULL;
	else
	{
		tail = head->prev;
		stack->top = head->next;
		stack->top->prev = tail;
		tail->next = stack->top;
	}
	popped_node->prev = NULL;
	popped_node->next = NULL;
	stack->size--;
	return (popped_node);
}

void	add_node_to_front(t_stack *stack, t_node *new_node)
{
	t_node	*head;
	t_node	*tail;

	if (!stack || !new_node)
		return ;
	if (stack->top == NULL)
	{
		stack->top = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		head = stack->top;
		tail = head->prev;
		new_node->prev = tail;
		new_node->next = head;
		head->prev = new_node;
		tail->next = new_node;
		stack->top = new_node;
	}
	stack->size++;
}

void	pa(t_stack *stack_a, t_stack *stack_b, int print_op)
{
	t_node	*head_b;

	head_b = pop_node_from_front(stack_b);
	if (!head_b)
		return ;
	add_node_to_front(stack_a, head_b);
	if (print_op)
		printf("pa\n");
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
		printf("pb\n");
	return ;
}

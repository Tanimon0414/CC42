/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_node_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:23:02 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/15 10:40:26 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_and_init_node(long num_val, t_stack **sa_ptr, t_stack **sb_ptr)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		stack_error(sa_ptr, sb_ptr);
	node->data = (int)num_val;
	node->index = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

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

void	elswap(t_stack *stack)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2022/10/20 07:24:59 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 09:01:10 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


int	rra(t_stack **a, int is_output)
{
	t_stack *head;
	t_stack *last;

	if (stack_size(*a) < 2)
		return (1);
	head = *a;
	last = find_last_node(head);
	while (head)
	{
		if (head->next->next == NULL)
		{
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
	last->next = *a;
	*a = last;
	if (is_output)
		ft_putstr_fd("rra\n", 1);
	return (0);
}

int	rrb(t_stack **b, int is_output)
{
	t_stack *head;
	t_stack *last;

	if (stack_size(*b) < 2)
		return (1);
	head = *b;
	last = find_last_node(head);
	while (head)
	{
		if (head->next->next == NULL)
		{
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
	last->next = *b;
	*b = last;
	if (is_output)
		ft_putstr_fd("rrb\n", 1);
	return (0);
}

int	rrr(t_stack **a, t_stack **b, int is_output)
{
	if (rra(a, 0) == 1 || rrb(b, 0) == 1)
		return (1);
	if (is_output)
		ft_putstr_fd("rrr\n", 1);
	return (0);
}

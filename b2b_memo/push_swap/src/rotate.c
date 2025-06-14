/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/10/20 07:08:21 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/20 07:22:58 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


int	ra(t_stack **a, int is_output)
{
	t_stack *head;
	t_stack *last;

	if (stack_size(*a) < 2)
		return (1);
	head = *a;
	last = find_last_node(head);
	if (!last)
		return (1);
	*a = head->next;
	head->next = NULL;
	last->next = head;
	if (is_output)
		ft_putstr_fd("ra\n", 1);
	return (0);
}

int	rb(t_stack **b, int is_output)
{
	t_stack *head;
	t_stack *last;

	if (stack_size(*b) < 2)
		return (1);
	head = *b;
	last = find_last_node(head);
	if (!last)
		return (1);
	*b = head->next;
	head->next = NULL;
	last->next = head;
	if (is_output)
		ft_putstr_fd("rb\n", 1);
	return (0);
}

int	rr(t_stack **a, t_stack **b, int is_output)
{
	if (ra(a, 0) == 1 || rb(b, 0) == 1)
		return (1);
	if (is_output)
		ft_putstr_fd("rr\n", 1);
	return (0);
}

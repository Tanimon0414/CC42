/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 06:49:44 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/20 07:07:32 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	pa(t_stack **a, t_stack **b, int is_output)
{
	t_stack	*tmp;
	t_stack	*to;
	t_stack	*from;

	if (stack_size(*b) == 0)
		return (1);
	to = *a;
	from = *b;
	tmp = from;
	from = from->next;
	*b = from;
	if (!to)
	{
		to = tmp;
		to->next = NULL;
		*a = to;
	}
	else
	{
		tmp->next = to;
		*a = tmp;
	}
	if (is_output)
		ft_putstr_fd("pa\n", 1);
	return (0);
}

int	pb(t_stack **a, t_stack **b, int is_output)
{
	t_stack	*tmp;
	t_stack	*to;
	t_stack	*from;

	if (stack_size(*a) == 0)
		return (1);
	to = *b;
	from = *a;
	tmp = from;
	from = from->next;
	*a = from;
	if (!to)
	{
		to = tmp;
		to->next = NULL;
		*b = to;
	}
	else
	{
		tmp->next = to;
		*b = tmp;
	}
	if (is_output)
		ft_putstr_fd("pb\n", 1);
	return (0);
}

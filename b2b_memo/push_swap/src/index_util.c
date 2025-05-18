/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:18:55 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 09:00:31 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	place_of_min_index(t_stack **stack, int beginning_value)
{
	int		min;
	t_stack	*head;

	head = *stack;
	min = head->i;
	while (head->next)
	{
		head = head->next;
		if ((head->i < min) && (head->i != beginning_value))
			min = head->i;
	}
	return (min);
}

int	place_of_max_index(t_stack **stack, int beginning_value)
{
	int		max;
	t_stack	*head;

	head = *stack;
	max = head->i;
	while (head->next)
	{
		head = head->next;
		if ((head->i > max) && (head->i != beginning_value))
			max = head->i;
	}
	return (max);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 06:09:43 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 09:06:57 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	sa(t_stack **a, int is_output)
{
	int		tmp_value;
	int		tmp_i;
	t_stack	*head;
	t_stack	*next;

	head = *a;
	next = head->next;
	if (stack_size(*a) < 2
		|| *a == NULL || head->next == NULL)
		return (1);
	tmp_value = head->value;
	head->value = next->value;
	next->value = tmp_value;
	tmp_i = head->i;
	head->i = next->i;
	next->i = tmp_i;
	if (is_output)
		ft_putstr_fd("sa\n", 1);
	return (0);
}

int	sb(t_stack **b, int is_output)
{
	int		tmp_value;
	int		tmp_i;
	t_stack	*head;
	t_stack	*next;

	head = *b;
	next = head->next;
	if (stack_size(*b) < 2
		|| *b == NULL || head->next == NULL)
		return (1);
	tmp_value = head->value;
	head->value = next->value;
	next->value = tmp_value;
	tmp_i = head->i;
	head->i = next->i;
	next->i = tmp_i;
	if (is_output)
		ft_putstr_fd("sb\n", 1);
	return (0);
}

int	ss(t_stack **a, t_stack **b, int is_output)
{
	if (sa(a, 0) == 1 || sa(b, 0) == 1)
		return (1);
	if (is_output)
		ft_putstr_fd("ss\n", 1);
	return (0);
}

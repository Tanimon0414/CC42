/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 09:05:53 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 09:00:50 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_stack	*create_new_node(int value)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->i = -1;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_stack	*find_last_node(t_stack *node)
{
	t_stack	*tmp;

	if (node == NULL)
		return (NULL);
	tmp = node;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_node_back(t_stack **node, t_stack *new)
{
	t_stack	*tmp;

	if (node == NULL)
		return ;
	if (!*node)
	{
		*node = new;
		(*node)->next = NULL;
	}
	else
	{
		tmp = find_last_node(*node);
		tmp->next = new;
		new->next = NULL;
	}
}

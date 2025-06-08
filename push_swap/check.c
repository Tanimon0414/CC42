/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:52:37 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/08 14:08:45 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_sorted(t_stack *stack)
{
	t_node	*current;
	int		i;

	current = stack->top;
	i = 0;
	while (i < stack->size)
	{
		if (current->index != i)
			break ;
		current = current->next;
	}
	if (current == NULL)
		return (1);
	return (0);
}

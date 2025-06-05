/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:25:33 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 13:45:11 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	debug_print_stack_values(t_stack *stack, const char *stack_name)
{
	t_node	*current;

	// まず、スタック自体がNULLでないか、スタック名がNULLでないかを確認
	if (stack_name == NULL)
		printf("Stack name is NULL.\n");
	else
		printf("%s: ", stack_name);
	printf("(size: %d) ", stack->size); // スタックのサイズも表示
	current = stack->top;
	// スタックの要素を -> でつないで表示
	while (current != NULL)
	{
		printf("%d", current->data);
		if (current->next != NULL)
		{
			printf(" -> ");
		}
		current = current->next;
	}
	printf(" -> NULL\n"); // リストの終端を示す
}

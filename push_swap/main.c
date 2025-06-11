/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:55:58 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/08 14:06:15 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
	{
		return (0);
	}
	initialize_stacks(&stack_a, &stack_b);
	check_and_set(argc, argv, &stack_a, &stack_b);
	set_index(stack_a);
	if (check_sorted(stack_a))
		return (0);
	sort_stacks(stack_a, stack_b);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}

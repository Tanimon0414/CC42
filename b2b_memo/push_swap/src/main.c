/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 06:51:46 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 09:00:39 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	**a;
	t_stack	**b;

	if (argc < 2)
		return (1);
	if (check_arg_illegality(argc, argv))
		write_error("Error");
	a = (t_stack **)malloc(sizeof(t_stack));
	b = (t_stack **)malloc(sizeof(t_stack));
	if (!a || !b)
		return (1);
	*a = NULL;
	*b = NULL;
	stack_init(a, argc, argv);
	if (is_stack_sorted(a))
	{
		free_stack(a);
		free_stack(b);
		return (0);
	}
	stack_sorting(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}

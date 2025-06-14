/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:09 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 15:44:23 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_overflow(long long acc, int digit, int sign)
{
	if (sign == 1)
	{
		if (acc > (INT_MAX - digit) / 10)
			return (0);
	}
	else
	{
		if (acc > (-(long long)INT_MIN - digit) / 10)
			return (0);
	}
	return (1);
}

static int	dup_check(t_stack *stack_a, int num)
{
	t_node	*current;
	int		i;

	if (!stack_a || !stack_a->top)
		return (1);
	current = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		if (current->data == num)
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}

static const char	*parse_sign_and_whitespace(const char *str, int *sign)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

int	strict_atoi(const char *str, int *out)
{
	long long	acc;
	int			sign;

	if (!str || !*str)
		return (0);
	sign = 1;
	str = parse_sign_and_whitespace(str, &sign);
	if (!ft_isdigit((unsigned char)*str))
		return (0);
	acc = 0;
	while (ft_isdigit((unsigned char)*str))
	{
		if (!check_overflow(acc, *str - '0', sign))
			return (0);
		acc = acc * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	*out = (int)(acc * sign);
	return (1);
}

void	check_and_set(int argc, char **argv, t_stack **stack_a_ptr,
		t_stack **stack_b_ptr)
{
	int		i;
	int		num_val;
	t_node	*new_node;

	i = 1;
	while (i < argc)
	{
		if (!strict_atoi(argv[i], &num_val))
			stack_error(stack_a_ptr, stack_b_ptr);
		if (!dup_check(*stack_a_ptr, num_val))
			stack_error(stack_a_ptr, stack_b_ptr);
		new_node = create_and_init_node(num_val, stack_a_ptr, stack_b_ptr);
		add_node_to_back(*stack_a_ptr, new_node);
		i++;
	}
}

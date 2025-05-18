/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 06:52:21 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/21 09:33:15 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../Libft/libft.h"

typedef struct s_stack
{
	int				i;
	int				value;
	struct s_stack	*next;
}	t_stack;

int		check_arg_illegality(int argc, char **argv);
long	ft_atol(const char *str);
void	write_error(char *str);
t_stack	*create_new_node(int value);
t_stack	*find_last_node(t_stack *node);
void	add_node_back(t_stack **node, t_stack *new);
void	stack_init(t_stack **stack, int argc, char **argv);
void	stack_indexing(t_stack **stack);
t_stack	*next_indexed_elem(t_stack **stack);
int		is_stack_sorted(t_stack **stack);
void	free_stack(t_stack **stack);
int		stack_size(t_stack *head);
void	stack_sorting(t_stack **a, t_stack **b);
void	small_sort(t_stack **a, t_stack **b);
int		place_of_min_index(t_stack **stack, int beginning_value);
int		place_of_max_index(t_stack **stack, int beginning_value);
void	sort_3_args(t_stack **stack);
void	sort_5_args(t_stack **a, t_stack **b);
void	radix_sort(t_stack **a, t_stack **b);
int		sa(t_stack **a, int is_output);
int		sb(t_stack **b, int is_output);
int		ss(t_stack **a, t_stack **b, int is_output);
int		pa(t_stack **a, t_stack **b, int is_output);
int		pb(t_stack **a, t_stack **b, int is_output);
int		ra(t_stack **b, int is_output);
int		rb(t_stack **b, int is_output);
int		rr(t_stack **a, t_stack **b, int is_output);
int		rra(t_stack **a, int is_output);
int		rrb(t_stack **b, int is_output);
int		rrr(t_stack **a, t_stack **b, int is_output);

#endif

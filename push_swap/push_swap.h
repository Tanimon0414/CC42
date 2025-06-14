/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:52:24 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/14 17:40:58 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_command
{
	int				all;
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rra;
	int				rb;
	int				rrb;
	int				rr;
	int				rrr;
}					t_command;

typedef struct s_node
{
	int				data;
	int				index;
	t_command		command;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	int				size;
}					t_stack;

/* --- 関数プロトタイプ宣言 --- */

/* 01_input_parsing.c */
void				check_and_set(int argc, char **argv, t_stack **sa_ptr,
						t_stack **sb_ptr);
int					strict_atoi(const char *str, int *out);

/* 02_stack_init.c */
void				initialize_stacks(t_stack **stack_a_ptr,
						t_stack **stack_b_ptr);
void				set_index(t_stack *stack_a);

/* 03_node_utils.c */
t_node				*create_and_init_node(long num_val, t_stack **sa_ptr,
						t_stack **sb_ptr);
void				add_node_to_back(t_stack *stack, t_node *new_node);
void				add_node_to_front(t_stack *stack, t_node *new_node);
t_node				*pop_node_from_front(t_stack *stack);
void				elswap(t_stack *stack);

/* 04_operations_push.c */
void				pa(t_stack *stack_a, t_stack *stack_b, int print_op);
void				pb(t_stack *stack_a, t_stack *stack_b, int print_op);

/* 05_operations_swap.c */
void				sa(t_stack *stack_a, int print_op);
void				sb(t_stack *stack_b, int print_op);
void				ss(t_stack *stack_a, t_stack *stack_b, int print_op);

/* 06_operations_rotate.c */
void				ra(t_stack *stack_a, int print_op);
void				rb(t_stack *stack_b, int print_op);
void				rr(t_stack *stack_a, t_stack *stack_b, int print_op);

/* 07_operations_rev_rotate.c */
void				rra(t_stack *stack_a, int print_op);
void				rrb(t_stack *stack_b, int print_op);
void				rrr(t_stack *stack_a, t_stack *stack_b, int print_op);

/* 08_sort_controller.c */
void				sort_stacks(t_stack *a, t_stack *b);

/* 09_sort_small.c */
void				sort_stacks_small(t_stack *stack_a, t_stack *stack_b);
void				sort_three(t_stack *a);

/* 10_cost_calculation.c */
void				count_commands_toa(t_stack *a, t_stack *b);
void				count_commands_tob(t_stack *a, t_stack *b);

/* 11_target_position.c */
int					target_pos_in_a(t_stack *a, int idx);
int					target_pos_in_b(t_stack *b, int idx);

/* 12_sort_utils.c */
void				align_min_on_top(t_stack *a);
int					find_min_pos(t_stack *s);
int					search_min(t_stack *a);
int					check_sorted(t_stack *stack);
void				init_commands(t_stack *stack_a);

/* 13_utils.c */
int					ft_min(int n1, int n2);
int					ft_max(int n1, int n2);
int					ft_abs(int n);

/*14_cost_utils.c*/
void				set_commands(int cost_a, int cost_b, int common,
						t_node *cur);
int					save_cost(int cost_a, int cost_b, t_node *cur);
int					rotation_cost(int size, int pos);

/* 99_error.c */
void				print_error_and_exit(void);
void				clear_stack(t_stack **stack_ptr);
void				stack_error(t_stack **stack_a_ptr, t_stack **stack_b_ptr);

#endif
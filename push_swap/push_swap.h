
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define ATOL_ERROR_VALUE ((long)INT_MAX + 1LL)
# define LLONG_CONVERSION_ERROR (LLONG_MAX - 1)

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdio.h> // デバッグ用
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

/* ------------------------ Function Prototypes ----------------------------- */

/* Argument validation and stack initialization (e.g., parser.c) */
void				parse_and_init_stack(int argc, char **argv,
						t_stack *stack_a);
int					is_sorted(t_stack *stack);
void				check_duplicate(t_stack *stack);

/* Stack operations (e.g., operations_basic.c, operations_rotate.c) */
void				sa(t_stack *stack_a, int print_op);
void				sb(t_stack *stack_b, int print_op);
void				ss(t_stack *stack_a, t_stack *stack_b, int print_op);
void				pa(t_stack *stack_a, t_stack *stack_b, int print_op);
void				pb(t_stack *stack_a, t_stack *stack_b, int print_op);
void				ra(t_stack *stack_a, int print_op);
void				rb(t_stack *stack_b, int print_op);
void				rr(t_stack *stack_a, t_stack *stack_b, int print_op);
void				rra(t_stack *stack_a, int print_op);
void				rrb(t_stack *stack_b, int print_op);
void				rrr(t_stack *stack_a, t_stack *stack_b, int print_op);

void				print_error_and_exit(void);
void				clear_stack(t_stack **stack_ptr);
void				stack_error(t_stack **stack_a_ptr, t_stack **stack_b_ptr);

void				initialize_stacks(t_stack **stack_a_ptr,
						t_stack **stack_b_ptr);
void				check_and_set(int argc, char **argv, t_stack **stack_a_ptr,
						t_stack **stack_b_ptr);
void				add_node_to_back(t_stack *stack, t_node *new_node);
t_node				*pop_node_from_front(t_stack *stack);
void				add_node_to_front(t_stack *stack, t_node *new_node);

void				set_index(t_stack *stack_a);
int					check_sorted(t_stack *stack);

long				ft_atol_strict(const char *str);

int					main(int argc, char **argv);

/* Debugging functions (e.g., debug.c) */
void				debug_print_stack_values(t_stack *stack,
						const char *stack_name);
void				debug_print_stack_index(t_stack *stack,
						const char *stack_name);

/* Sorting algorithm (e.g., algorithm.c, sort_small.c) */
void				sort_stacks(t_stack *stack_a, t_stack *stack_b);
void				sort_three_elements(t_stack *stack_a);
// void    assign_indices(t_stack *stack_a); // ソート後のインデックスを各ノードに割り当て
// ... (コスト計算やノード移動戦略の関数)

#endif

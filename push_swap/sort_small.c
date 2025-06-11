/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:52:54 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/10 23:52:54 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* stack 内で最小 index を持つノードの位置を返す */
int find_min_pos(t_stack *s)
{
    t_node *cur;
    int     min_idx;
    int     min_pos;
    int     i;

    cur = s->top;
    min_idx = INT_MAX;
    min_pos = 0;
    i = 0;
    while (i < s->size)
    {
        if (cur->index < min_idx)
        {
            min_idx = cur->index;
            min_pos = i;
        }
        cur = cur->next;
        i++;
    }
    return min_pos;
}


void sort_three(t_stack *a)
{
    int x = a->top->data;
    int y = a->top->next->data;
    int z = a->top->prev->data;   /* bottom */

    if (x > y && y < z && x < z)
        sa(a,1);           // 2 1 3
    else if (x > y && y > z)            
    {
        sa(a,1);
        rra(a,1);
    } // 3 2 1
    else if (x > y && y < z && x > z)   
        ra(a,1);           // 3 1 2
    else if (x < y && y > z && x < z)   
    {
        sa(a,1);
        ra(a,1);
    } // 2 3 1
    else if (x < y && y > z && x > z)   
        rra(a,1);          // 1 3 2
}

void ra_or_rra(t_stack *stack_a, t_stack *stack_b, int pos)
{
    if (pos <= stack_a->size / 2)
    {
        int j = 0;
        while (j < pos)
        {
            ra(stack_a, 1);
            j++;
        }
    }
    else
    {
        int j = pos;
        while (j < stack_a->size)
        {
            rra(stack_a, 1);
            j++;
        }
    }
}

void sort_stacks_small(t_stack *stack_a, t_stack *stack_b)
{
    if (stack_a->size == 2 && !check_sorted(stack_a))
        sa(stack_a, 1);
    else if (stack_a->size == 3)
        sort_three(stack_a);
    else if (stack_a->size <= 5)
    {
        while (stack_a->size > 3)
        {
            int pos = find_min_pos(stack_a);
            ra_or_rra(stack_a, stack_b, pos);
            pb(stack_a, stack_b, 1);
        }
        sort_three(stack_a);
        while (stack_b->size > 0)
            pa(stack_a, stack_b, 1);
    }
}

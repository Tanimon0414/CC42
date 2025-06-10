/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:04:05 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/10 09:04:05 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int pos_in_stack(t_stack *s, t_node *n)
{

}
/* その node を B に push するとき、
   B のどこに入るのが正しいかをインデックスで返す */
int target_pos_in_b(t_stack *b, int node_index_in_a)
{
    
    
}

/* 符号付きコストを返す。正なら ra/rb、負なら rra/rrb を使う */
int rotation_cost(int size, int pos)
{
    if(pos <= size / 2)
        return(pos);
    else
        return(pos - size);
}

static void sort_three(t_stack *a)
{
    int x = a->top->data;
    int y = a->top->next->data;
    int z = a->top->prev->data;   /* bottom */

    if (x > y && y < z && x < z)        sa(a,1);           // 2 1 3
    else if (x > y && y > z)            { sa(a,1); rra(a,1);} // 3 2 1
    else if (x > y && y < z && x > z)   ra(a,1);           // 3 1 2
    else if (x < y && y > z && x < z)   { sa(a,1); ra(a,1);} // 2 3 1
    else if (x < y && y > z && x > z)   rra(a,1);          // 1 3 2
}

void sort_stacks_small(t_stack *a, t_stack *b)
{
    if (a->size == 2 && !check_sorted(a))
        sa(a, 1);
    else if (a->size == 3)
        sort_three(a);
    else if (a->size <= 5)
    {
        while (a->size > 3)
        {
            int pos = find_min_pos(a);
            if (pos <= a->size / 2)
            {
                int j = 0;
                while (j < pos)
                {
                    ra(a, 1);
                    j++;
                }
            }
            else
            {
                int j = pos;
                while (j < a->size)
                {
                    rra(a, 1);
                    j++;
                }
            }
            pb(a, b, 1);
        }
        sort_three(a);
        while (b->size > 0)
            pa(a, b, 1);
    }
}

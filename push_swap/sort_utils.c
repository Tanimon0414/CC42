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





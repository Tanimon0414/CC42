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

/*  B→A 用: A を **昇順** に保つための挿入位置を返す                         */
int target_pos_in_a(t_stack *a, int idx)
{
    t_node *cur;
    int     i;
    int     target;
    int     diff;

    if (a->size == 0)
        return (0);

    /* 1) idx より小さくて最小差のノードの "次" をトップにしたい   */
    cur   = a->top;
    i     = 0;
    diff  = INT_MAX;
    target= -1;
    while (i < a->size)
    {
        if (cur->index < idx && idx - cur->index < diff)
        {
            diff   = idx - cur->index;
            target = (i + 1) % a->size;     /* cur の直後 */
        }
        cur = cur->next;
        i++;
    }
    if (target != -1)
        return (target);

    /* 2) すべてより小 or 大 ⇒ min_idx ノードの位置              */
    cur        = a->top;
    i          = 0;
    int min_idx = INT_MAX;
    int min_pos = 0;
    while (i < a->size)
    {
        if (cur->index < min_idx)
        {
            min_idx = cur->index;
            min_pos = i;
        }
        cur = cur->next;
        i++;
    }
    return (min_pos);
}


/*  A→B 用: B を **降順**(大きい index が上) に保つ位置を返す                 */
int target_pos_in_b(t_stack *b, int idx)
{
    t_node *cur;
    int     i;
    int     target;
    int     diff;

    if (b->size == 0)
        return (0);

    /* 1) idx より大きくて最小差のノードを探す → その位置にセット */
    cur   = b->top;
    i     = 0;
    diff  = INT_MAX;
    target= -1;
    while (i < b->size)
    {
        if (cur->index > idx && cur->index - idx < diff)
        {
            diff   = cur->index - idx;
            target = i;
        }
        cur = cur->next;
        i++;
    }
    if (target != -1)                /* 見つかった */
        return (target);

    /* 2) すべてより大 or 小 ⇒ max_idx を持つノードを探す位置を返す */
    cur   = b->top;
    i     = 0;
    int max_idx  = INT_MIN;
    int max_pos  = 0;
    while (i < b->size)
    {
        if (cur->index > max_idx)
        {
            max_idx = cur->index;
            max_pos = i;
        }
        cur = cur->next;
        i++;
    }
    return (max_pos);
}

/* 符号付きコストを返す。正なら ra/rb、負なら rra/rrb を使う */
int rotation_cost(int size, int pos)
{
    if(pos <= size / 2)
        return(pos);
    else
        return(pos - size);
}





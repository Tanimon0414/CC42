/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:22:01 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/08 20:48:21 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// minをtopに持ってくる
void align_min_on_top(t_stack *a)
{
    int pos;

    pos = find_min_pos(a);
    if (pos <= a->size / 2)
    {
        int i = 0;
        while (i < pos)
        {
            ra(a, 1);
            i++;
        }
    }
    else
    {
        int i = pos;
        while (i < a->size)
        {
            rra(a, 1);
            i++;
        }
    }
}


/* 3. n+2 条件を使って即決 / さもなくば最小コスト */
static int search_min(t_stack *a)
{
    t_node *cur;
    int     i;
    int     best_idx;
    int     best_cost;

    cur = a->top;
    i = 0;
    best_idx = 0;
    best_cost = INT_MAX;
    while (i < a->size)
    {
        if (cur->command.all <= i + 2)
            return i; /* n+2 条件を満たしたら即返す */
        if (cur->command.all < best_cost)
        {
            best_cost = cur->command.all;
            best_idx  = i;
        }
        cur = cur->next;
        i++;
    }
    return best_idx;
}

/* 4. 実際に rr / ra … を回して pb */
static void exec_rot(t_stack *a, t_stack *b, t_command *c)
{
    while (c->rr  > 0) 
    {
        rr(a, b, 1);  
        c->rr--;
    }
    while (c->rrr > 0) 
    {
        rrr(a, b, 1);
        c->rrr--;
    }
    while (c->ra  > 0) 
    {
        ra(a, 1);
        c->ra--;
    }
    while (c->rra > 0) 
    {
        rra(a, 1);
        c->rra--;
    }
    while (c->rb  > 0) 
    {
        rb(b, 1);
        c->rb--;
    }
    while (c->rrb > 0) 
    {
        rrb(b, 1);
        c->rrb--;
    }
}

static void move_node(int idx, t_stack *a, t_stack *b)
{
    t_node *cur;
    int     i;

    cur = a->top;
    i = 0;
    while (i < idx)
    {
        cur = cur->next;
        i++;
    }
    exec_rot(a, b, &cur->command);
    pb(a, b, 1);
}

void sort_stacks(t_stack *a, t_stack *b)
{
    int move_idx;

    if (a->size <= 5)
    {
        sort_stacks_small(a, b);
        return;
    }

    /* 初手: とりあえず 2 個 A→B */
    pb(a, b, 1);
    pb(a, b, 1);

    /* main loop: A が 3 になるまで */
    while (a->size > 3)
    {
        init_commands(a);
        count_commands(a, b);
        move_idx = search_min(a);
        move_node(move_idx, a, b);
    }
    sort_three(a);
    /* B から戻す: A 昇順になる位置で pa */
    while (b->size > 0)
    {
        /* B 側ノードに cost を入れるために
           A/B を入れ替えて呼び出す */
        init_commands(b);

        /* reuse count_commands but with role flipped */
        /* ごく小数なので単純版でも OK */
       
        move_idx = search_min(b);
        /* exec_rot() は a,b の向きが逆なので、逆向け wrapper */

	}
    align_min_on_top(a);
}

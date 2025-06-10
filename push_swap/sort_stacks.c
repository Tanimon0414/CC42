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

/* 2. A→B 用コスト計算 */
static void count_commands(t_stack *a, t_stack *b)
{
    t_node *cur;
    int     i;

    cur = a->top;
    i = 0;
    while (i < a->size)
    {
        int cost_a;
        int pos_b;
        int cost_b;
        int common;

        cost_a = rotation_cost(a->size, i);
        pos_b  = target_pos_in_b(b, cur->index);
        cost_b = rotation_cost(b->size, pos_b);

        common = 0;
        if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
        {
            int abs_a = ft_abs(cost_a);
            int abs_b = ft_abs(cost_b);
            common   = ft_min(abs_a, abs_b);

            if (cost_a >= 0)
                cur->command.rr  = common;
            else
                cur->command.rrr = common;
        }

        /* 個別回転数 */
        cur->command.ra  = ft_max(cost_a, 0) - common;
        cur->command.rra = ft_max(-cost_a, 0) - common;
        cur->command.rb  = ft_max(cost_b, 0) - common;
        cur->command.rrb = ft_max(-cost_b, 0) - common;

        /* 合計 +1(pb) */
        cur->command.all = cur->command.ra + cur->command.rra +
                           cur->command.rb + cur->command.rrb +
                           cur->command.rr + cur->command.rrr + 1;
        cur = cur->next;
        i++;
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
    while (c->rr  > 0) { rr(a, b, 1);  c->rr--;  }
    while (c->rrr > 0) { rrr(a, b, 1); c->rrr--; }
    while (c->ra  > 0) { ra(a, 1);      c->ra--;  }
    while (c->rra > 0) { rra(a, 1);     c->rra--; }
    while (c->rb  > 0) { rb(b, 1);      c->rb--;  }
    while (c->rrb > 0) { rrb(b, 1);     c->rrb--; }
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


static void set_commands(t_stack *stack_a)
{
    t_node *cur = stack_a->top;
    int i = 0;
    while (i < stack_a->size)
    {
        ft_bzero(&cur->command, sizeof(t_command));
        cur = cur->next;
        i++;
    }
}



void sort_stacks(t_stack *a, t_stack *b)
{
    int move_idx;

    if (check_sorted(a))
        return;
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
        set_commands(a);
        count_commands(a, b);
        move_idx = search_min(a);
        move_node(move_idx, a, b);
    }

    /* A(3) を確定 */
    sort_three(a);

    /* B から戻す: A 昇順になる位置で pa */
    while (b->size > 0)
    {
        /* B 側ノードに cost を入れるために
           A/B を入れ替えて呼び出す */
        set_commands(b);

        /* reuse count_commands but with role flipped */
        /* ごく小数なので単純版でも OK */
       
        move_idx = search_min(b);
        /* exec_rot() は a,b の向きが逆なので、逆向け wrapper */

	}
    align_min_on_top(a);
}

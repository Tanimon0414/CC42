/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:06:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/11 00:06:41 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void set_commands(int cost_a, int cost_b, int common, t_node *cur)
{
     /* 個別回転数 */
    cur->command.ra  = ft_max(cost_a, 0) - common;
    cur->command.rra = ft_max(-cost_a, 0) - common;
    cur->command.rb  = ft_max(cost_b, 0) - common;
    cur->command.rrb = ft_max(-cost_b, 0) - common;
    /* 合計 +1(pb) */
    cur->command.all = cur->command.ra + cur->command.rra +
                       cur->command.rb + cur->command.rrb +
                       cur->command.rr + cur->command.rrr + 1;
}

static int save_cost(int cost_a, int cost_b, t_node *cur)
{
    int common;
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
    return(common);
}

/* count_commands.c */

void count_commands_toa(t_stack *a, t_stack *b)
{
    t_node *cur = b->top;          /* ← 1. ループ対象を B に */
    int     i   = 0;

    while (i < b->size)            /* ← 2. ループ上限も B */
    {
        int cost_b;                /* B 側の回転コスト */
        int pos_a;                 /* A での挿入位置      */
        int cost_a;                /* A 側の回転コスト    */
        int common;

        cost_b = rotation_cost(b->size, i);          /* ← 3. B のサイズ */
        pos_a  = target_pos_in_a(a, cur->index);     /* 挿入点検索 */
        cost_a = rotation_cost(a->size, pos_a);      /* ← 4. A のサイズ */
        common = save_cost(cost_a, cost_b, cur);     /* 共通 rr/rrr を決定 */
        set_commands(cost_a, cost_b, common, cur);   /* 個別回転数を格納 */

        cur = cur->next;
        i++;
    }
}



void count_commands_tob(t_stack *a, t_stack *b)
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
        common = save_cost(cost_a, cost_b, cur);
        set_commands(cost_a, cost_b, common, cur);
        cur = cur->next;
        i++;
    }
}


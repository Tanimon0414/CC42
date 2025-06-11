/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:05:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/11 00:05:41 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void init_commands(t_stack *stack_a)
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

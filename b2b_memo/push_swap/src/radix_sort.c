/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/10/21 09:31:41 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/22 08:54:21 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


static int	count_bit_digit(t_stack **stack) {
  t_stack *head;
  int max_num;
  int bit_digit;

  head = *stack;
  max_num = head->i;
  bit_digit = 0;
  while (head) {
    if (head->i > max_num)
      max_num = head->i;
    head = head->next;
  }
  while ((max_num >> bit_digit) != 0)
    bit_digit++;
  return (bit_digit);
}

void	radix_sort(t_stack **a, t_stack **b) {
  int i;
  int j;
  int size_a;
  int max_bits;
  t_stack *head_a;

  head_a = *a;
  size_a = stack_size(head_a);
  max_bits = count_bit_digit(a);
  i = 0;
  while (i < max_bits) {
    j = 0;
    while (j++ < size_a) {
      head_a = *a;
      if (((head_a->i >> i) & 1) == 1)
        ra(a, 1);
      else
        pb(a, b, 1);
    }
    while (stack_size(*b) > 0)
      pa(a, b, 1);
    i++;
  }
}

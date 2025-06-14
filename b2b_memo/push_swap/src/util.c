/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/10/13 07:08:18 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/17 09:07:29 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	write_error(char *str) {
  ft_putendl_fd(str, 2);
  exit(1);
}

int	is_numeric(char *c) {
  int i;

  i = 0;
  if (c[i] == '-')
    i++;
  while (c[i]) {
    if (!ft_isdigit(c[i]))
      return (0);
    i++;
  }
  return (1);
}

int	exist_duplicates(char **args, long tmp, size_t i) {
  i++;
  while (args[i]) {
    if (ft_atol(args[i]) == tmp)
      return (1);
    i++;
  }
  return (0);
}

int	check_arg_illegality(int argc, char **argv) {
  size_t i;
  char **args;
  long tmp;

  i = 0;
  if (argc < 2)
    return (1);
  else if (argc == 2)
    args = ft_split(argv[1], ' ');
  else {
    i = 1;
    args = argv;
  }
  while (args[i]) {
    tmp = ft_atol(args[i]);
    if (!is_numeric(args[i]) || exist_duplicates(args, tmp, i) ||
        (tmp < -2147483648 || tmp > 2147483647))
      return (1);
    i++;
  }
  if (argc == 2)
    free(args);
  return (0);
}

int	is_stack_sorted(t_stack **stack) {
  t_stack *head;

  head = *stack;
  while (head && head->next) {
    if ((head->value) > (head->next->value))
      return (0);
    head = head->next;
  }
  return (1);
}

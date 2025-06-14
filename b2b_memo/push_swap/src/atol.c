/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2022/10/13 08:45:42 by kishigam          #+#    #+#             */
/*   Updated: 2022/10/15 07:17:52 by kishigam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


typedef struct s_num {
  int sign;
  long figures;
} t_num;

static int	ft_isspace(char c) {
  if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\f') || (c == '\r') ||
      (c == '\v'))
    return (1);
  else
    return (0);
}

long	ft_atol(const char *str) {
  t_num num;

  num.sign = 0;
  num.figures = 0;
  while (ft_isspace(*str))
    str++;
  if (*str == '+') {
    str++;
    if (*str == '-')
      return (num.figures);
  }
  if (*str == '-') {
    num.sign = 1;
    str++;
  }
  while ('0' <= *str && *str <= '9') {
    num.figures = num.figures * 10 + (long)*str - '0';
    str++;
  }
  if (num.sign == 1)
    return ((-1) * num.figures);
  return (num.figures);
}

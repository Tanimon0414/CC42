/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2025/04/28 15:14:47 by atanimot          #+#    #+#             */
/*   Updated: 2025/04/30 12:33:01 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static size_t	num_len(int n) {
  size_t len;

  len = (n <= 0);
  while (n) {
    n /= 10;
    len++;
  }
  return (len);
}

char	*ft_itoa(int n) {
  size_t len;
  char *str;
  long nb;

  len = num_len(n);
  str = (char *)malloc(len + 1);
  nb = n;
  if (!str)
    return (NULL);
  str[len] = '\0';
  if (nb < 0) {
    str[0] = '-';
    nb = -nb;
  }
  if (nb == 0)
    str[0] = '0';
  while (nb > 0) {
    str[--len] = '0' + (nb % 10);
    nb /= 10;
  }
  return (str);
}

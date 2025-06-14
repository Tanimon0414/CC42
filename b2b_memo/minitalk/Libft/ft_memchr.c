/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/03/08 14:50:25 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/08 17:03:26 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	*ft_memchr(const void *s, int c, size_t n) {
  size_t i;

  i = 0;
  while (i < n) {
    if (((unsigned char *)s)[i] == (unsigned char)c)
      return ((void *)s + i);
    i++;
  }
  return (NULL);
}

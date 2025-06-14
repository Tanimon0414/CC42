/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/01/04 19:10:40 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/10 09:30:40 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	*ft_memmove(void *dst, const void *src, size_t n) {
  unsigned char *p;
  unsigned char *q;

  p = (unsigned char *)dst;
  q = (unsigned char *)src;
  if (p == NULL && q == NULL)
    return (dst);
  if (p < q)
    ft_memcpy(dst, src, n);
  else
    while (n--)
      *(p + n) = *(q + n);
  return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/01/11 16:51:13 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/10 19:00:27 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	ft_strlcat(char *restrict dst, const char *restrict src,
                  size_t dstsize) {
  size_t dst_len;
  size_t src_len;

  dst_len = ft_strlen(dst);
  src_len = ft_strlen(src);
  dst += dst_len;
  if (dstsize > dst_len)
    ft_strlcpy(dst, src, dstsize - dst_len);
  if (dstsize < dst_len)
    return (src_len + dstsize);
  return (dst_len + src_len);
}

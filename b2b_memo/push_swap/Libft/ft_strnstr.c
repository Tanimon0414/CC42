/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/03/08 15:44:41 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 15:55:01 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strnstr(const char *haystack, const char *needle, size_t len) {
  size_t i;
  size_t j;

  if (!*needle)
    return ((char *)haystack);
  i = 0;
  while (haystack[i] && (size_t)i < len) {
    if (haystack[i] == needle[0]) {
      j = 0;
      while (haystack[i + j] == needle[j] && i + j < len) {
        if (needle[j + 1] == '\0')
          return ((char *)&haystack[i]);
        j++;
      }
    }
    i++;
  }
  return (0);
}

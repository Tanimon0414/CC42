/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/03/09 23:21:06 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/10 01:11:49 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static size_t	get_list_size(const char *s, char c) {
  size_t count;

  count = 0;
  while (*s && s++) {
    while (*s != c && *s)
      s++;
    count++;
    while (*s == c && *s)
      s++;
  }
  return (count);
}

static int	fill_list(char const *s, char c, char **list) {
  size_t i;
  size_t len;

  i = 0;
  while (*s) {
    len = 0;
    while (*s != c && *s && ++s)
      len++;
    list[i] = malloc(len + 1);
    if (!list[i]) {
      while (i)
        free(list[--i]);
      free(list);
      return (1);
    }
    ft_strlcpy(list[i++], s - len, len + 1);
    while (*s == c && *s)
      s++;
  }
  list[i] = 0;
  return (0);
}

char	**ft_split(const char *s, char c) {
  char **list;

  if (!s)
    return (NULL);
  while (*s == c && *s)
    s++;
  list = (char **)malloc(sizeof(char *) * (get_list_size(s, c) + 1));
  if (!list)
    return (NULL);
  if (fill_list(s, c, list))
    return (NULL);
  return (list);
}

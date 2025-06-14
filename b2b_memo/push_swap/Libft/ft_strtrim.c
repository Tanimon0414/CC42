/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2022/03/08 17:37:39 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 11:14:40 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static int	is_trim_possible(char c, char const *set) {
  int count;

  count = -1;
  while (set[++count])
    if (set[count] == c)
      return (1);
  return (0);
}

static int	get_size(char const *s1, char const *set) {
  int count;
  int size;

  size = ft_strlen(s1);
  count = 0;
  while (is_trim_possible(s1[size - count - 1], set))
    count++;
  return (size - count);
}

char	*ft_strtrim(char const *s1, char const *set) {
  int count;
  int size;
  char *str;

  count = 0;
  size = 0;
  if (!s1)
    return (0);
  if (!set)
    return (ft_strdup(s1));
  while (is_trim_possible(s1[count], set))
    count++;
  if (count == (int)ft_strlen(s1))
    return (ft_strdup(""));
  size = get_size(s1 + count, set) + 1;
  str = (char *)malloc((size) * sizeof(char));
  if (!str)
    return (NULL);
  ft_strlcpy(str, s1 + count, size);
  return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2025/04/28 12:53:59 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/09 16:14:56 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static size_t	count_words(const char *s, char c) {
  size_t n;

  n = 0;
  while (*s) {
    while (*s && *s == c)
      s++;
    if (*s) {
      n++;
      while (*s && *s != c)
        s++;
    }
  }
  return (n);
}

static char	*dup_word(const char *start, size_t len) {
  char *word;
  size_t i;

  word = (char *)malloc(len + 1);
  if (!word)
    return (NULL);
  i = 0;
  while (i < len) {
    word[i] = start[i];
    i++;
  }
  word[i] = '\0';
  return (word);
}

static void	free_all(char **tab) {
  size_t i;

  if (!tab)
    return ;
  i = 0;
  while (tab[i])
    free(tab[i++]);
  free(tab);
}

static int	add_word(char **tab, size_t *idx, const char **p, char c) {
  size_t len;

  len = 0;
  while ((*p)[len] && (*p)[len] != c)
    len++;
  tab[*idx] = dup_word(*p, len);
  if (!tab[*idx])
    return (0);
  (*idx)++;
  *p += len;
  return (1);
}

char	**ft_split(char const *s, char c) {
  char **tab;
  const char *ptr;
  size_t i;

  if (!s)
    return (NULL);
  tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
  if (!tab)
    return (NULL);
  i = 0;
  ptr = s;
  while (*ptr) {
    if (*ptr == c)
      ptr++;
    else if (!add_word(tab, &i, &ptr, c))
      return (free_all(tab), NULL);
  }
  tab[i] = NULL;
  return (tab);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	**res;
// 	size_t	i;

// 	/* テスト文字列と区切り文字（この例ではカンマ） */
// 	res = ft_split("Hello,world,,42tokyo", ',');
// 	if (!res)
// 	{
// 		fprintf(stderr, "ft_split returned NULL\n");
// 		return (EXIT_FAILURE);
// 	}
// 	/* 分割結果を出力 */
// 	for (i = 0; res[i] != NULL; i++)
// 		printf("res[%zu] = \"%s\"\n", i, res[i]);
// 	/* メモリ解放 */
// 	for (i = 0; res[i] != NULL; i++)
// 		free(res[i]);
// 	free(res);
// 	return (EXIT_SUCCESS);
// }

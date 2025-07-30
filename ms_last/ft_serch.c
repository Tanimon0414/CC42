/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_serch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:24 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/28 18:10:50 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	char	*cur;

	if (!*to_find)
	{
		return (str);
	}
	cur = str;
	while (*cur != '\0')
	{
		i = 0;
		while (cur[i] != '\0' && to_find[i] != '\0')
		{
			if (cur[i] != to_find[i])
				break ;
			i++;
		}
		if (to_find[i] == '\0')
			return (cur);
		cur++;
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;

	last_occurrence = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_occurrence = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last_occurrence);
}

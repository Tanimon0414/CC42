/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:32 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/30 12:50:18 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	size_t	memory;
	char	*copy;
	int		i;

	memory = 0;
	while ((char)src[memory] != '\0')
		memory++;
	memory = memory + 1;
	copy = (char *)malloc(memory * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while ((char)src[i] != '\0')
	{
		copy[i] = (char)src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	len;
	char	*copy;

	len = 0;
	while (src[len] && len < n)
		len++;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:29 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:30 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *str, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)str[i] != (unsigned char)s2[i])
			return ((unsigned char)str[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

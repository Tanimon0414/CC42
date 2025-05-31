/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:54:25 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/09 19:18:28 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < dstsize && dst[dlen])
		dlen++;
	if (dlen == dstsize)
		return (dstsize + slen);
	i = 0;
	while (src[i] && dlen + i + 1 < dstsize)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

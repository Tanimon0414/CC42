/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/01/04 18:58:37 by keisuke           #+#    #+#             */
/*   Updated: 2022/02/14 03:02:02 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *p;
	unsigned char *q;

	p = (unsigned char *)dst;
	q = (unsigned char *)src;
	if (p == NULL && q == NULL)
		return (dst);
	while (n--)
		*p++ = *q++;
	return (dst);
}

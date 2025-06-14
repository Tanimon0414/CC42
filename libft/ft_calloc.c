/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/04/25 21:03:54 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/06 21:04:32 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>


void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t total;
	unsigned char *ptr;
	size_t i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	total = nmemb * size;
	if (total / nmemb != size)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
		ptr[i++] = 0;
	return ((void *)ptr);
}

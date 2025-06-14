/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2022/03/08 16:34:57 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 12:14:52 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	*ft_calloc(size_t count, size_t size)
{
	void *pointer;

	pointer = (char *)malloc(size * count);
	if (!pointer)
		return (NULL);
	return (ft_memset(pointer, 0, size * count));
}

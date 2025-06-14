/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/03/09 09:17:13 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 09:21:55 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_striteri(char *s, void (*f)(unsigned int, char *)) {
  size_t i;

  if (s == NULL || f == NULL)
    return ;
  i = 0;
  while (s[i] != '\0') {
    f((unsigned int)i, &s[i]);
    i++;
  }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/03/09 10:07:21 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 10:07:38 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstadd_back(t_list **lst, t_list *new) {
  t_list *last;

  if (lst == NULL)
    return ;
  if (*lst == NULL)
    *lst = new;
  else {
    last = ft_lstlast(*lst);
    last->next = new;
  }
}

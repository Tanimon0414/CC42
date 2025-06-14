/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.C                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2022/03/09 10:17:48 by keisuke           #+#    #+#             */
/*   Updated: 2022/03/09 10:20:07 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstclear(t_list **lst, void (*del)(void *)) {
  t_list *node;

  if (lst == NULL)
    return ;
  while (*lst != NULL) {
    node = (*lst)->next;
    ft_lstdelone(*lst, del);
    *lst = node;
  }
}

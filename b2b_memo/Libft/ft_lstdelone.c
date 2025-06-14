/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: keisuke <keisuke.130@icloud.com>           +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2022/01/30 05:09:39 by hnakatan          #+#    #+#             */
/*   Updated: 2022/03/09 10:15:23 by keisuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstdelone(t_list *lst, void (*del)(void *)) {
  if (lst == NULL || del == NULL)
    return ;
  del(lst->content);
  free(lst);
}

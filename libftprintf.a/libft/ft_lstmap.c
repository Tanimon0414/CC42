/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:28:41 by atanimot          #+#    #+#             */
/*   Updated: 2025/05/09 16:28:36 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*current;
	void	*temp_content;

	new_list = NULL;
	current = lst;
	if (!lst || !f || !del)
		return (NULL);
	while (current)
	{
		temp_content = f(current->content);
		new_node = ft_lstnew(temp_content);
		if (!new_node)
		{
			del(temp_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}


#include "list.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*current;
	int		swapped;
	int		tmp;

	current = lst;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (current->next)
		{
			if (!(*cmp)(current->data, current->next->data))
			{
				swapped = 1;
				tmp = current->data;
				current->data = current->next->data;
				current->next->data = tmp;
			}
			current = current->next;
		}
		current = lst;
	}
	return (lst);
}

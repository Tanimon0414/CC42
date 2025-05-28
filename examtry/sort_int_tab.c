
#include <stdio.h>

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int				tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j + 1 < size)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	// i = 0;
	// while (i < size)
	// {
	// 	printf("%d\n", tab[i]);
	// 	i++;
	// }
	return ;
}

int	main(void)
{
	int	tab[] = {3, 4, 2, 5, 1, 24, 1, 3};
	int	size;

	size = 8;
	sort_int_tab(tab, size);
	return (0);
}

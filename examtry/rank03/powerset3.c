
#include <stdio.h>
#include <stdlib.h>

int	*set_num(int *set, char **argv)
{
	int	i;

	i = 2;
	while (argv[i])
	{
		set[i - 2] = atoi(argv[i]);
		i++;
	}
	return (set);
}

void	print_ans(int *set, int *check, int len)
{
	int	i;
	int	first;

	i = 0;
	first = 0;
	while (i < len)
	{
		if (check[i] == 1)
		{
			if (first)
				printf(" ");
			printf("%d", set[i]);
			first = 1;
		}
		i++;
	}
	if (first)
		printf("\n");
	return ;
}

void	cal_set(int sum, int *set, int *check, int len, int cur_index,
		int *first)
{
	if (cur_index == len)
	{
		if (sum == 0)
		{
			(*first) = 1;
			print_ans(set, check, len);
		}
		return ;
	}
	cal_set(sum, set, check, len, cur_index + 1, first);
	check[cur_index] = 1;
	cal_set(sum - set[cur_index], set, check, len, cur_index + 1, first);
	check[cur_index] = 0;
	return ;
}

int	main(int argc, char **argv)
{
	int	sum;
	int	*set;
	int	len;
	int	*check;
	int	first;

	first = 0;
	if (argc <= 2)
		return (0);
	sum = atoi(argv[1]);
	len = argc - 2;
	set = malloc(sizeof(int) * (len));
	if (!set)
		return (1);
	set = set_num(set, argv);
	check = calloc(sizeof(int), len);
	if (!check)
	{
		free(set);
		return (1);
	}
	cal_set(sum, set, check, len, 0, &first);
	if (!first || sum == 0)
		printf("\n");
	free(set);
	free(check);
	return (0);
}


#include <stdio.h>
#include <stdlib.h>

int	*set_num(int *set, int len, char **argv)
{
	int	i;

	i = 0;
	while (i < len)
	{
		set[i] = atoi(argv[i + 2]);
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
	printf("\n");
	return ;
}

int	not_emp(int *check, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (check[i] > 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_loop(int *ans_num, int sum, int *set, int *check, int len,
		int index)
{
	if (index == len)
	{
		if (sum == 0 && not_emp(check, len))
		{
			print_ans(set, check, len);
			(*ans_num) = 1;
		}
		return ;
	}
	check_loop(ans_num, sum, set, check, len, index + 1);
	check[index] = 1;
	check_loop(ans_num, sum - set[index], set, check, len, index + 1);
	check[index] = 0;
	return ;
}

int	main(int argc, char **argv)
{
	int	sum;
	int	*set;
	int	len;
	int	*check;
	int	ans_num;

	if (argc <= 2)
		return (0);
	sum = atoi(argv[1]);
	len = argc - 2;
	set = malloc(sizeof(int) * len);
	if (!set)
		return (1);
	set = set_num(set, len, argv);
	check = calloc(sizeof(int), len);
	if (!check)
		return (1);
	ans_num = 0;
	check_loop(&ans_num, sum, set, check, len, 0);
	if (!ans_num)
		printf("\n");
	return (0);
}

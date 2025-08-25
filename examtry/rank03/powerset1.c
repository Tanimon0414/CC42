#include <stdio.h>
#include <stdlib.h>

//全探索
int	*num_len(char **argv, int *len)
{
	int	i;
	int	tmp;
	int	*set;

	i = 2;
	while (argv[i])
		i++;
	(*len) = i - 2;
	set = malloc(sizeof(int) * (*len));
	if (!set)
		return (NULL);
	i = 2;
	while (argv[i])
	{
		tmp = atoi(argv[i]);
		set[i - 2] = tmp;
		i++;
	}
	return (set);
}

void	print_ans(int *set, int *check, int len)
{
	int	first_print;

	first_print = 1;
	for (int i = 0; i < len; i++)
	{
		if (check[i] == 1)
		{
			if (!first_print)
				printf(" ");
			printf("%d", set[i]);
			first_print = 0;
		}
	}
	printf("\n");
}

// Corrected recursive function
void	find_subsets(int sum, int *set, int *check, int len, int index)
{
	// Base Case: We have processed all the numbers in the set (reached the end).
	if (index == len)
	{
		// NOW we check if the sum is zero. If it is, we found a valid subset.
		if (sum == 0)
		{
			print_ans(set, check, len);
		}
		return ;
	}
	// Recursive Step: Explore two paths for the current element set[index].
	// Path 1: Exclude the current number and move to the next.
	find_subsets(sum, set, check, len, index + 1);
	// Path 2: Include the current number.
	check[index] = 1;
	find_subsets(sum - set[index], set, check, len, index + 1);
	// Backtrack: Undo the choice for other recursive paths.
	check[index] = 0;
}

int	main(int argc, char **argv)
{
	int	sum;
	int	len;
	int	*set;
	int	*check;

	if (argc <= 2)
		return (0);
	sum = atoi(argv[1]);
	set = num_len(argv, &len);
	if (!set)
		return (1);
	check = calloc(len, sizeof(int));
	if (!check)
	{
		free(set);
		return (1);
	}
	find_subsets(sum, set, check, len, 0);
	free(set);
	free(check);
	return (0);
}

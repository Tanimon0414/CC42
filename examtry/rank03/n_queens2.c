
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 13:15~

void	print_array(int *array, int col)
{
	int	first;

	first = 0;
	for (int i = 0; i < col; i++)
	{
		if (first)
			fprintf(stdout, " ");
		fprintf(stdout, "%d", array[i]);
		first = 1;
	}
	fprintf(stdout, "\n");
	return ;
}

int	check_array(int *array, int cur_index, int i)
{
	for (int j = 0; j < cur_index; j++)
	{
		if (array[j] == i || array[j] - j == i - cur_index || array[j] + j == i
			+ cur_index)
			return (0);
	}
	return (1);
}

void	set_array(int *array, int col, int cur_index)
{
	if (cur_index == col)
	{
		print_array(array, col);
		return ;
	}
	for (int i = 0; i < col; i++)
	{
		if (check_array(array, cur_index, i))
		{
			array[cur_index] = i;
			set_array(array, col, cur_index + 1);
		}
	}
	return ;
}

int	main(int argc, char **argv)
{
	int	col;

	if (argc != 2)
		return (0);
	col = atoi(argv[1]);
	int array[col]; // fix;
	set_array(array, col, 0);
	return (0);
}

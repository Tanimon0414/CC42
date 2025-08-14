

#include <stdio.h>
#include <stdlib.h>

void	print_sol(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, "%s", " ");
		else
			fprintf(stdout, "%s", "\n");
		i++;
	}
}

int	is_safe(int *board, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row || (board[i] - row == col - i) || (row
				- board[i] == col - i))
			return (0);
		i++;
	}
	return (1);
}

void	solve(int *board, int col, int n)
{
	int	row;

	if (col == n)
	{
		print_sol(board, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	n;

	if (ac != 2)
		return (0);
	n = atoi(av[1]);
	int board[n]; //固定用
	if (n <= 0)
		return (0);
	solve(board, 0, n);
}

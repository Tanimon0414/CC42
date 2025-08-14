
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	write_sol(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
		i++;
	}
	return ;
}

int	check(int *board, int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row || row - board[i] == col - i || board[i]
			- row == col - i)
			return (0);
		i++;
	}
	return (1);
}

void	solve(int *board, int n, int col)
{
	int	row;

	row = 0;
	if (col == n)
	{
		write_sol(board, n);
		return ;
	}
	while (row < n)
	{
		if (check(board, row, col))
		{
			board[col] = row;
			solve(board, n, col + 1);
		}
		row++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int	n;

	if (argc != 2)
		return (0);
	n = atoi(argv[1]);
	if (n <= 3)
		return (0);
	int board[n]; // fix
	solve(board, n, 0);
	return (0);
}

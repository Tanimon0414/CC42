
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	**reset_board(int n)
{
	int		i;
	int		j;
	bool	board[n][n];

	return (board);
}

int	main(int argc, char **argv)
{
	int		n;
	int		i;
	int		j;
	bool	**board;

	n = atoi(argv[1]);
	if (n)
		i = 0;
	if (argc != 2)
		return (0);
	board = reset_board(n);
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			printf("%d ", board[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

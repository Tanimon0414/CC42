
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	while (argc == 2 && argv[1][i])
	{
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
		{
			write(1, "_", 1);
			argv[1][i] = argv[1][i] + 32;
		}
		write(1, &argv[1][i], 1);
		i++;
	}
	return (write(1, "\n", 1), 0);
}

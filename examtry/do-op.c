
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	main(int argc, char **argv)
{
	int a;
	int b;

	if (argc == 4 && !argv[2][1])
	{
		a = atoi(argv[1]);
		b = atoi(argv[3]);
		if (argv[2][0] == '+')
			printf("%d", a + b);
		else if (argv[2][0] == '-')
			printf("%d", a - b);
		else if (argv[2][0] == '*')
			printf("%d", a * b);
		else if (argv[2][0] == '/')
			printf("%d", a / b);
		else if (argv[2][0] == '%')
			printf("%d", a % b);
	}
	printf("\n");
	return (0);
}

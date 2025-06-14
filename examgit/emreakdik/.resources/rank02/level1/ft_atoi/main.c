
int	ft_atoi(const char *str);
#include <stdio.h>
#include <stdlib.h>


int	main(int argc, char **argv)
{
	(void)argc;
	printf("ft_atoi(\"%s\") = %d\n", argv[1], ft_atoi(argv[1]));
	return (0);
}

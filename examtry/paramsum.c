
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
	return ;
}

void	ft_putunbr(unsigned int n)
{
	if (n >= 10)
		ft_putunbr(n / 10);
	else
		ft_putchar(n % 10 + '0');
	return ;
}

int	main(int argc, char **argv)
{
	(void)argv;
	ft_putunbr(argc - 1);
	return (write(1, "\n", 1), 0);
}

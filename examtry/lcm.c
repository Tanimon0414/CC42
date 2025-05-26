

unsigned int	saikou(unsigned int a, unsigned int b)
{
	unsigned int	n;

	if (a < b)
	{
		n = a;
		while (n > 0)
		{
			if (a % n == 0 && b % n == 0)
				return (n);
			n--;
		}
	}
	else
	{
		n = b;
		while (n > 0)
		{
			if (a % n == 0 && b % n == 0)
				return (n);
			n--;
		}
	}
	return (n);
}

unsigned int	lcm(unsigned int a, unsigned int b)
{
	int	hcf;

	if (a == 0 || b == 0)
		return (0);
	hcf = saikou(a, b);
	return ((a / hcf) * b);
}

#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;

	a = 243;
	b = 91;
	printf("%d\n", lcm(a, b));
	return (0);
}

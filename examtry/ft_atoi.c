
int	ft_atoi(const char *str)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		n = n * 10 + (*str++ - '0');
	return (n * sign);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = "      -420";
// 	printf("%d\n", ft_atoi(str));
// 	return (0);
// }

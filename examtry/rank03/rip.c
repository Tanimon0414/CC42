
#include <stdio.h>
#include <unistd.h>

int	count_num(int *left, int *right, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			(*left)++;
		else if (str[i] == ')')
			(*right)++;
		else if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_ans(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '(')
			res++;
		else if (str[i] == ')')
			res--;
		if (res < 0)
			return (0);
		i++;
	}
	if (res != 0)
		return (0);
	return (1);
}

void	print_ans(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, " \n", 2);
	return ;
}

void	change_loop(int N, int n, char c, char *str, int len, int index)
{
	if (index == len)
	{
		if (n == 0 && check_ans(str))
			print_ans(str);
		return ;
	}
	if (str[index] != c)
		change_loop(N, n, c, str, len, index + 1);
	else
	{
		change_loop(N, n, c, str, len, index + 1);
		str[index] = ' ';
		change_loop(N - 1, n - 1, c, str, len, index + 1);
		str[index] = c;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int	right;
	int	left;
	int	i;
	int	len;

	i = 0;
	if (argc != 2)
		return (0);
	right = 0;
	left = 0;
	if (!count_num(&left, &right, argv[1]))
		return (0);
	len = ft_strlen(argv[1]);
	if (left > right)
		change_loop(left, left - right, '(', argv[1], len, 0);
	else if (right > left)
		change_loop(right, right - left, ')', argv[1], len, 0);
	else
	{
		while (argv[1][i])
		{
			write(1, &argv[1][i], 1);
			i++;
		}
		write(1, " \n", 2);
	}
	return (0);
}

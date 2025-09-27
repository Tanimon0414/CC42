// 14:38~
#include <stdio.h>
#include <unistd.h>

void	count_par(char *str, int *left, int *right)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			(*left)++;
		else if (str[i] == ')')
			(*right)++;
	}
	return ;
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_str(char *str)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			pos++;
		else if (str[i] == ')')
			pos--;
		if (pos < 0)
			return (0);
		i++;
	}
	if (pos == 0)
		return (1);
	return (0);
}

void	print_ans(char *str)
{
	for (int i = 0; str[i]; i++)
		write(1, &str[i], 1);
	write(1, " \n", 2);
	return ;
}

void	change_par(char take, int num, char *str, int len, int p)
{
	if (p == len)
	{
		if (num == 0)
		{
			if (check_str(str))
				print_ans(str);
		}
		return ;
	}
	// while (str[p])
	// {
	// 	if (str[p] == take)
	// 	{
	// 		change_par(take, num, str, len, p + 1);
	// 		str[p] = ' ';
	// 		change_par(take, num - 1, str, len, p + 1);
	// 		str[p] = take;
	// 	}
	// 	p++;
	// }ミス
	if (str[p] != take)
		change_par(take, num, str, len, p + 1);
	else
	{
		// change_par(take, num, str, len, p + 1);
		str[p] = ' ';
		change_par(take, num - 1, str, len, p + 1);
		str[p] = take;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int	right;
	int	left;
	int	len;

	if (argc != 2)
		return (0);
	right = 0;
	left = 0;
	count_par(argv[1], &left, &right);
	len = ft_strlen(argv[1]);
	if (left == right)
	{
		if (check_str(argv[1]))
			print_ans(argv[1]);
	}
	else if (left > right)
		change_par('(', left - right, argv[1], len, 0);
	else if (left < right)
		change_par(')', right - left, argv[1], len, 0);
	return (0);
}

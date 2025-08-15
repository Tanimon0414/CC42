
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	len = 0;
	i = 0;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	cal_num(int len)
{
	int	n;

	if (len <= 1)
		return (1);
	return (len * cal_num(len - 1));
}

char	*bubble_sort(char *str, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (str[j] > str[j + 1] && str[j + 1])
			{
				tmp = str[j + 1];
				str[j + 1] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (str);
}

void	sort_and_puts(char *ordered, int num, int len, int move_idx)
{
	int	count;

	count = cal_num(len - move_idx - 1, 1);
	if (count == 1)
	{
	}
}

int	main(int argc, char **argv)
{
	int		len;
	int		num;
	char	*ordered;
	char	**all;
	int		move_idx;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (!len)
		return (0);
	num = cal_num(len);
	all = malloc(sizeof(char *) * num);
	ordered = malloc(sizeof(char) * len + 1);
	ordered = bubble_sort(argv[1], len);
	printf("len = %d, num = %d, ordered = %s\n", len, num, ordered);
	return (0);
	move_idx = len - 1;
	while (move_idx >= 0)
	{
		sort_and_puts(ordered, num, len, move_idx);
		move_idx--;
	}
	return (0);
}

// int	main(void)
// {
// 	// puts() を使用
// 	puts("Hello from puts()!");
// 	puts("This is a second line.");
// 	// 比較のために printf() を使用
// 	printf("Hello from printf()!");
// 	printf("This is on the same line.");
// 	return (0);
// }


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

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	sort_perm(char **all, int num)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < num - 1)
	{
		j = 0;
		while (j < num - i - 1)
		{
			if (ft_strcmp(all[j], all[j + 1] > 0))
			{
				tmp = all[j + 1];
				all[j + 1] = all[j];
				all[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	put_perm(char **all, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		puts(all[i]);
		i++;
	}
	return ;
}

void	gen_all_perm(char **all, char *str, int *row, int current_index,
		int len)
{
	char	tmp;
	int		i;

	if (current_index == len)
	{
		ft_strcpy(all[(*row)], str);
		(*row)++;
		return ;
	}
	i = current_index;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[current_index];
		str[current_index] = str[i];
		gen_all_perm(all, str, row, current_index + 1, len);
		tmp = str[i];
		str[i] = str[current_index];
		str[current_index] = str[i];
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int		len;
	int		num;
	char	**all;
	int		row;
	int		i;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (!len)
		return (0);
	num = cal_num(len);
	all = malloc(sizeof(char *) * num);
	i = 0;
	while (i < num)
	{
		all[i] = malloc(sizeof(char) * (len + 1));
		i++;
	}
	row = 0;
	gen_all_perm(all, argv[1], &row, 0, len);
	sort_perm(all, num);
	put_perm(all, num);
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

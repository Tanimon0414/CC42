
#include <stdio.h>
#include <stdlib.h>

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

int	cal_perm(int n)
{
	if (n <= 1)
		return (1);
	return (n * cal_perm(n - 1));
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	set_perm(char *str, char **all, int len, int *row, int cur_index)
{
	char	tmp;

	if (cur_index == len)
	{
		all[(*row)] = ft_strcpy(all[(*row)], str);
		(*row)++;
		return ;
	}
	for (int i = cur_index; i < len; i++)
	{
		tmp = str[i];
		str[i] = str[cur_index];
		str[cur_index] = tmp;
		set_perm(str, all, len, row, cur_index + 1);
		tmp = str[i];
		str[i] = str[cur_index];
		str[cur_index] = tmp;
	}
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_perm(char **all, int perm)
{
	char	*tmp;

	for (int i = 0; i < perm - 1; i++)
	{
		for (int j = 0; j < perm - i - 1; j++)
		{
			if (ft_strcmp(all[j], all[j + 1]) > 0)
			{
				tmp = all[j];
				all[j] = all[j + 1];
				all[j + 1] = tmp;
			}
		}
	}
	return ;
}

void	print_perm(char **all, int perm)
{
	for (int i = 0; i < perm; i++)
		puts(all[i]);
	return ;
}

int	main(int argc, char **argv)
{
	int		len;
	int		perm;
	char	**all;
	int		row;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	perm = cal_perm(len);
	all = malloc(sizeof(char *) * perm);
	for (int i = 0; i < perm; i++)
	{
		all[i] = malloc(sizeof(char) * len + 1);
		all[i][len] = '\0';
	}
	row = 0;
	set_perm(argv[1], all, len, &row, 0);
	sort_perm(all, perm);
	print_perm(all, perm);
	for (int i = 0; i < perm; i++)
		free(all[i]);
	free(all);
	return (0);
}

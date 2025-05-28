
#include <stdlib.h>

int	count_words(char *str)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str == '\0')
			break ;
		words++;
		while (*str && *str != ' ' && *str != '\t' && *str != '\n')
			str++;
	}
	return (words);
}

int	words_len(char *str, int j)
{
	int	len;

	len = 0;
	while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '\n')
	{
		len++;
		j++;
	}
	return (len);
}

char	*set_words(char *str, int *j)
{
	int		len;
	char	*busu;
	int		i;

	len = words_len(str, *j);
	busu = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		busu[i] = str[*j];
		i++;
		(*j)++;
	}
	busu[i] = '\0';
	return (busu);
}

char	**ft_split(char *str)
{
	char	**res;
	int		words;
	int		num;
	int		i;

	words = count_words(str);
	res = malloc((sizeof(char *)) * (words + 1));
	num = 0;
	i = 0;
	while (num < words)
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		res[num] = set_words(str, &i);
		num++;
	}
	res[num] = NULL;
	return (res);
}

#include <stdio.h>

int	main(void)
{
	char	*str;
	char	**res;
	int		i;

	str = "abc  			\t 	def 		gh ";
	res = ft_split(str);
	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (0);
}

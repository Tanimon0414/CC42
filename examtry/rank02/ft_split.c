
// #include <stdlib.h>

// int	count_words(char *str)
// {
// 	int	words;

// 	words = 0;
// 	while (*str)
// 	{
// 		while (*str == ' ' || *str == '\t' || *str == '\n')
// 			str++;
// 		if (*str == '\0')
// 			break ;
// 		words++;
// 		while (*str && *str != ' ' && *str != '\t' && *str != '\n')
// 			str++;
// 	}
// 	return (words);
// }

// int	words_len(char *str, int j)
// {
// 	int	len;

// 	len = 0;
// 	while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '\n')
// 	{
// 		len++;
// 		j++;
// 	}
// 	return (len);
// }

// char	*set_words(char *str, int *j)
// {
// 	int		len;
// 	char	*busu;
// 	int		i;

// 	len = words_len(str, *j);
// 	busu = malloc(sizeof(char) * (len + 1));
// 	i = 0;
// 	while (i < len)
// 	{
// 		busu[i] = str[*j];
// 		i++;
// 		(*j)++;
// 	}
// 	busu[i] = '\0';
// 	return (busu);
// }

// char	**ft_split(char *str)
// {
// 	char	**res;
// 	int		words;
// 	int		num;
// 	int		i;

// 	words = count_words(str);
// 	res = malloc((sizeof(char *)) * (words + 1));
// 	num = 0;
// 	i = 0;
// 	while (num < words)
// 	{
// 		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
// 			i++;
// 		res[num] = set_words(str, &i);
// 		num++;
// 	}
// 	res[num] = NULL;
// 	return (res);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;
// 	char	**res;
// 	int		i;

// 	str = "abc  			\t 	def 		gh ";
// 	res = ft_split(str);
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>

int	count_words(char *str)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] == '\0')
			break ;
		words++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	printf("ok");
	return (words);
}

int	fuckin_strlen(char *str, int j)
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

char	*set_words(char *str, int *i)
{
	int		len;
	char	*busu;
	int		j;

	j = 0;
	len = fuckin_strlen(str, *i);
	busu = malloc((sizeof(char)) * (len + 1));
	while (j < len)
	{
		busu[j] = str[*i];
		(*i)++;
		j++;
	}
	busu[j] = '\0';
	return (busu);
}

char	**ft_split(char *str)
{
	int		words;
	char	**res;
	int		i;
	int		num;

	num = 0;
	i = 0;
	words = count_words(str);
	res = malloc((sizeof(char *) * (words + 1)));
	while (num < words)
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		res[num] = set_words(str, &i);
		num++;
	}
	res[num] = NULL;
	while (num--)
		printf("%s\n", res[num]);
	return (res);
}

int	main(void)
{
	char	*str;

	// char	**test;
	str = "  \t  abc  de  f \t ";
	ft_split(str);
	return (0);
}

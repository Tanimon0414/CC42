
#include <aio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j] && s[i] != reject[j])
			j++;
		if (!reject[j])
			count++;
		else
			break ;
		i++;
	}
	return (count);
}

#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s;
	char	*reject;

	s = "abcdefg";
	reject = "fuga";
	printf("%zu\n", strcspn(s, reject));
	printf("%zu\n", ft_strcspn(s, reject));
	return (0);
}

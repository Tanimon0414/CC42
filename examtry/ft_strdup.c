
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

#include <string.h>

int	main(void)
{
	char	*src;

	src = "Ya-man   !!";
	printf("%s\n", ft_strdup(src));
	printf("%s\n", strdup(src));
	return (0);
}

#include <stdio.h>
#include <string.h>

int    ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/* 
int	main(void)
{
	printf("%d\n", strcmp("te", "tes"));
	printf("%d\n", ft_strcmp("te", "tes"));
} */

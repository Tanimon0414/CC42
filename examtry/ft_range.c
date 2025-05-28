
#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	size;
	int	*result;
	int	i;

	size = abs(end - start) + 1;
	result = malloc((sizeof(int)) * size);
	if (!result)
		return (NULL);
	i = 0;
	if (end >= start)
	{
		while (end >= start)
		{
			result[i] = start;
			i++;
			start++;
		}
	}
	else
	{
		while (end <= start)
		{
			result[i] = start;
			i++;
			start--;
		}
	}
	return (result);
}

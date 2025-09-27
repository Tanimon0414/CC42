
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (n > 0 && *s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*input_buffer;
	char	*temp_buffer;
	char	*search_str;
	size_t	search_len;
	ssize_t	bytes_read;
	size_t	total_size;
	size_t	SIZE;

	SIZE = 4096;
	if (argc != 2 || !argv[1][0])
		return (1);
	input_buffer = NULL;
	search_str = argv[1];
	search_len = strlen(argv[1]);
	total_size = 0;
	while (1)
	{
		temp_buffer = realloc(input_buffer, total_size + SIZE);
		if (!temp_buffer)
		{
			perror("Error");
			free(input_buffer);
			return (1);
		}
		input_buffer = temp_buffer;
		bytes_read = read(0, input_buffer + total_size, SIZE);
		if (bytes_read < 0)
		{
			perror("Error");
			free(input_buffer);
			return (1);
		}
		if (bytes_read == 0)
			break ;
		total_size += bytes_read;
	}
	for (size_t i = 0; i < total_size;)
	{
		if (i + search_len <= total_size && ft_strncmp(input_buffer + i,
				search_str, search_len) == 0)
		{
			for (size_t j = 0; j < search_len; j++)
				printf("*");
			i += search_len;
		}
		else
		{
			printf("%c", input_buffer[i]);
			i++;
		}
	}
	return (0);
}


#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if ((char)c == '\0')
		return (s);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest || !src)
		return (NULL);
	if (n == 0)
		return (dest);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	char	*new_str;
	size_t	s1_len;

	if (!s1 || !s2)
		return (0);
	s1_len = 0;
	if (*s1)
		s1_len = ft_strlen(*s1);
	new_str = (char *)malloc(s1_len + size2 + 1);
	if (!new_str)
		return (0);
	if (*s1)
	{
		ft_memcpy(new_str, *s1, s1_len);
		free(*s1);
	}
	ft_memcpy(new_str + s1_len, s2, size2);
	new_str[s1_len + size2] = '\0';
	*s1 = new_str;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

// ft_memmove 不要

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*res;
	char		*tmp;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	res = NULL;
	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&res, b))
		{
			free(res);
			return (NULL);
		}
		bytes_read = read(fd, b, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(res);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		b[bytes_read] = '\0';
		tmp = ft_strchr(b, '\n');
	}
	if (tmp)
	{
		if (!str_append_mem(&res, b, tmp - b))
		{
			free(res);
			return (NULL);
		}
		ft_memcpy(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	}
	else if (res && ft_strlen(res) > 0)
	{
		b[0] = '\0';
		return (res);
	}
	else
	{
		return (NULL);
	}
	return (res);
}

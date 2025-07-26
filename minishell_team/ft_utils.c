#include "minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num != 0 && size > 4294967295 / num)
		return (NULL);
	ptr = (void *)malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)dest;
	while (i < count)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < count)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	char	*cur;

	if (!*to_find)
	{
		return (str);
	}
	cur = str;
	while (*cur != '\0')
	{
		i = 0;
		while (cur[i] != '\0' && to_find[i] != '\0')
		{
			if (cur[i] != to_find[i])
				break ;
			i++;
		}
		if (to_find[i] == '\0')
			return (cur);
		cur++;
	}
	return (0);
}


char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t	memory;
	char	*copy;
	int		i;

	memory = 0;
	while ((char)src[memory] != '\0')
		memory++;
	memory = memory + 1;
	copy = (char *)malloc(memory * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while ((char)src[i] != '\0')
	{
		copy[i] = (char)src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	len;
	char	*copy;

	len = 0;
	while (src[len] && len < n)
		len++;

	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);

	i = 0;
	while (i < len)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *str, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)str[i] != (unsigned char)s2[i])
			return ((unsigned char)str[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	if (!str)
		return (0);
	while ((char)str[length])
	{
		length++;
	}
	return (length);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static size_t	count_words(const char *s, char c)
{
	size_t i = 0, count = 0;
	while (s[i])
    {
		while (s[i] == c)
			i++;
		if (!s[i])
            break;
		count++;
		if (is_quote(s[i]))
        {
			char quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i]) i++;
		} else {
			while (s[i] && s[i] != c && !is_quote(s[i]))
				i++;
		}
	}
	return count;
}

static char	*extract_word(const char *s, size_t *i, char c)
{
	size_t	start = *i;
	size_t	end;
	char	quote;

	if (is_quote(s[*i]))
	{
		quote = s[(*i)++];
		start = *i;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		end = *i;
		if (s[*i])
			(*i)++;
	}
	else
	{
		while (s[*i] && s[*i] != c && !is_quote(s[*i]))
			(*i)++;
		end = *i;
	}
	char *word = malloc(end - start + 1);
	if (!word)
		return NULL;
	ft_memcpy(word, s + start, end - start);
	word[end - start] = '\0';
	return word;
}

char	**ft_split(const char *s, char c)
{
	if (!s) return NULL;
	size_t i = 0;
    size_t j = 0;
    size_t len = count_words(s, c);
	char **result = malloc(sizeof(char *) * (len + 1));
	if (!result) return NULL;
	while (s[i]) {
		while (s[i] == c)
			i++;
		if (s[i])
			result[j++] = extract_word(s, &i, c);
	}
	result[j] = NULL;
	return result;
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	if (!ptr)
		return malloc(new_size);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return NULL;

	size_t copy_size = old_size < new_size ? old_size : new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return new_ptr;
}







long long   ft_atoll(char *c)
{
    int     i;
    int     sign;
    long long tmp;
    long long   result;

    i = 0;
    sign = 1;
    result = 0;
    while (c[i] == ' ' || (c[i] >= 9 && c[i] <= 13))
        i++;
    if (c[i] == '-' || c[i] == '+')
    {
        if (c[i++] == '-')
            sign = -1;
    }
    while (c[i])
    {
        if (!(c[i] >= '0' && c[i] <= '9'))
        {
            write(1, "exit\n", 5);
            write(STDERR_FILENO, "exit: ", 6);
            write(STDERR_FILENO, c, ft_strlen(c));
            write(STDERR_FILENO, ": numeric argument required\n", 28);
            exit (2);
        }
        tmp = result;
        result = result * 10 + (c[i] - '0');
        if (result / 10 != tmp)
        {
            write(1, "exit\n", 5);
            write(STDERR_FILENO, "exit: ", 6);
            write(STDERR_FILENO, c, ft_strlen(c));
            write(STDERR_FILENO, ": numeric argument required\n", 28);
            exit (2);
        }
        i++;
    }
    printf("exit\n");
    return (result * sign);
}

char	*ft_strjoin(char const *str, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		j++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:27 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:28 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(const char *s, char c, size_t i, size_t count)
{
	char	quote;

	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
		{
			while (s[i] && s[i] != c && !is_quote(s[i]))
				i++;
		}
	}
	return (count);
}

static char	*create_substring(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	len;

	len = end - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, s + start, len);
	word[len] = '\0';
	return (word);
}

static char	*extract_word(const char *s, size_t *i, char c)
{
	size_t	start;
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
		start = *i;
		while (s[*i] && s[*i] != c && !is_quote(s[*i]))
			(*i)++;
		end = *i;
	}
	return (create_substring(s, start, end));
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**result;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	len = count_words(s, c, 0, 0);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			result[j++] = extract_word(s, &i, c);
	}
	result[j] = NULL;
	return (result);
}

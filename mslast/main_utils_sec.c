/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:14:11 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/30 11:47:30 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_replace(const char *str, size_t start, size_t len,
		const char *replace)
{
	char	*result;
	size_t	replace_len;
	size_t	str_len;
	size_t	result_len;

	if (!str || !replace)
		return (NULL);
	replace_len = ft_strlen(replace);
	str_len = ft_strlen(str);
	result_len = str_len - len + replace_len;
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, start);
	ft_memcpy(result + start, replace, replace_len);
	ft_memcpy(result + start + replace_len, str + start + len, str_len - (start
			+ len));
	result[result_len] = '\0';
	return (result);
}

static char	*get_path_for_tilde_expansion(t_shell *shell)
{
	char	*path_var;
	char	*first_path;
	char	*processed_path;
	char	*colon_pos;
	char	*last_slash;

	path_var = get_env_value("PATH", shell->envp);
	if (!path_var)
		return (NULL);
	colon_pos = ft_strchr(path_var, ':');
	if (colon_pos)
		first_path = ft_strndup(path_var, colon_pos - path_var);
	else
		first_path = ft_strdup(path_var);
	if (!first_path)
		return (NULL);
	last_slash = ft_strrchr(first_path, '/');
	if (last_slash && last_slash != first_path)
		processed_path = ft_strndup(first_path, last_slash - first_path);
	else
		processed_path = ft_strdup(first_path);
	free(first_path);
	return (processed_path);
}

static void	update_quote_state(char c, bool *in_s_quote, bool *in_d_quote)
{
	if (c == '\'' && !*in_d_quote)
		*in_s_quote = !*in_s_quote;
	else if (c == '\"' && !*in_s_quote)
		*in_d_quote = !*in_d_quote;
}

static void	replace_tilde_at_pos(char **line, int *i, const char *path)
{
	char	*temp;
	char	next_char;

	next_char = (*line)[*i + 1];
	if (next_char == '\0' || next_char == '/' || next_char == ' '
		|| next_char == '\t')
	{
		temp = *line;
		*line = str_replace(temp, *i, 1, path);
		free(temp);
		*i += ft_strlen(path) - 1;
	}
}

char	*expand_tilde_in_line(char *line, t_shell *shell)
{
	char	*path;
	bool	in_s_quote;
	bool	in_d_quote;
	int		i;

	path = get_path_for_tilde_expansion(shell);
	if (!path)
		return (line);
	in_s_quote = false;
	in_d_quote = false;
	i = 0;
	while (line[i])
	{
		update_quote_state(line[i], &in_s_quote, &in_d_quote);
		if (line[i] && line[i] == '~' && !in_s_quote && !in_d_quote && (i == 0
				|| line[i - 1] == ' ' || line[i - 1] == '\t'))
			replace_tilde_at_pos(&line, &i, path);
		i++;
	}
	free(path);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:45 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/29 14:06:43 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_str(const char *s1, const char *s2, const char *s3)
{
	if (s1)
		write(STDERR_FILENO, s1, ft_strlen(s1));
	if (s2)
		write(STDERR_FILENO, s2, ft_strlen(s2));
	if (s3)
		write(STDERR_FILENO, s3, ft_strlen(s3));
}

char	**copy_envp(char **envp)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	is_quoted_whitespace(const char *str)
{
	size_t	len;
	char	quote_char;
	size_t	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	quote_char = str[0];
	if (quote_char != '\'' && quote_char != '"')
		return (0);
	if (str[len - 1] != quote_char)
		return (0);
	i = 1;
	while (i < len - 1)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->envp = copy_envp(envp);
	shell->last_status = 0;
}

char	*join_lines_for_quotes(char *line, char *newline)
{
	char	*prompt_str;
	size_t	line_len;
	size_t	newline_len;

	line_len = ft_strlen(line);
	newline_len = ft_strlen(newline);
	prompt_str = malloc(line_len + newline_len + 2);
	if (!prompt_str)
	{
		free(line);
		free(newline);
		return (NULL);
	}
	ft_strcpy(prompt_str, line);
	prompt_str[line_len] = '\n';
	ft_strcpy(prompt_str + line_len + 1, newline);
	free(line);
	free(newline);
	return (prompt_str);
}

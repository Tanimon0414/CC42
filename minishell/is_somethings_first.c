/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_somethings_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:40 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:41 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "<<"));
}

int	is_operator(const char *s)
{
	return (is_redirection(s) || !ft_strcmp(s, "|"));
}

int	is_all_redirection_chars(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (s[i] != '>' && s[i] != '<')
			return (0);
		i++;
	}
	return (1);
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

int	is_unclosed_quote(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_something.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:21:38 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:21:39 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*two_char_op(const char *s)
{
	if (!s[0] || !s[1])
		return (NULL);
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (s);
	return (NULL);
}

int	check_redirection_errors(t_cmd *cmds)
{
	t_cmd	*current;
	int		has_error;

	current = cmds;
	has_error = 0;
	while (current)
	{
		if (current->infile == -1 || current->outfile == -1)
		{
			has_error = 1;
		}
		current = current->next;
	}
	return (has_error);
}

int	contains_operator_char(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	contains_unquoted_dollar(const char *s)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (quote == 0)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		if (s[i] == '$' && quote != '\'')
			return (1);
		i++;
	}
	return (0);
}

int	has_whitespace(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			return (1);
		str++;
	}
	return (0);
}

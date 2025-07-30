/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_somethings_second.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:43 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:44 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_fd_redirection(const char *s)
{
	if (!s || !s[0] || !s[1])
		return (0);
	if ((s[0] >= '0' && s[0] <= '9') && (s[1] == '>' || s[1] == '<'))
		return (1);
	return (0);
}

int	is_empty_or_whitespace(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

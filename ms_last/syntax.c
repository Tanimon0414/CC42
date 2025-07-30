/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:15 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:23:16 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(const char *msg1, const char *token,
		const char *msg2, t_shell *shell)
{
	put_error_str(msg1, token, msg2);
	shell->last_status = 2;
	return (0);
}

static int	validate_long_redirection(const char *cur, t_shell *shell)
{
	if (is_all_redirection_chars(cur) && ft_strlen(cur) > 2)
	{
		return (syntax_error("syntax error near unexpected token `", cur,
				"'\n", shell));
	}
	return (1);
}

static int	validate_token_after_redirection(const char *next, t_shell *shell)
{
	if (!next)
	{
		return (syntax_error("syntax error near unexpected token `newline'\n",
				NULL, NULL, shell));
	}
	if (is_operator(next))
	{
		return (syntax_error("syntax error near unexpected token `", next,
				"'\n", shell));
	}
	if (contains_operator_char(next))
	{
		return (syntax_error("syntax error near unexpected token `newline'\n",
				NULL, NULL, shell));
	}
	return (1);
}

int	validate_syntax_tokens(t_token *tokens, t_shell *shell)
{
	int			i;
	const char	*cur;
	const char	*next;

	i = 0;
	while (tokens[i].value)
	{
		cur = tokens[i].value;
		next = tokens[i + 1].value;
		if (!validate_long_redirection(cur, shell))
			return (0);
		if (is_redirection(cur))
		{
			if (!validate_token_after_redirection(next, shell))
				return (0);
		}
		i++;
	}
	return (1);
}

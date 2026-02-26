/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:06 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:23:07 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new_token(t_token **tok_ptr, size_t *j, size_t *cap,
		char *value)
{
	size_t	old_size;

	if (*j + 1 >= *cap)
	{
		old_size = sizeof(t_token) * (*cap);
		*cap *= 2;
		*tok_ptr = ft_realloc(*tok_ptr, old_size, sizeof(t_token) * (*cap));
	}
	(*tok_ptr)[*j].value = value;
	(*tok_ptr)[*j].quote = 0;
	(*j)++;
}

static bool	try_parse_operator(const char *s, t_parse_state *parse)
{
	char	op[4];

	ft_bzero(op, 4);
	if (s[parse->i] == '>' && s[parse->i + 1] == '|')
	{
		add_new_token(&parse->tok, &parse->j, &parse->cap,
			ft_strndup(&s[parse->i], 2));
		return (parse->i += 2, true);
	}
	if (two_char_op(&s[parse->i]) || is_fd_redirection(&s[parse->i]))
	{
		op[0] = s[parse->i];
		op[1] = s[parse->i + 1];
		if (s[parse->i + 1] == '>' && s[parse->i + 2] == '>')
			op[2] = s[(parse->i)++];
		add_new_token(&parse->tok, &parse->j, &parse->cap, ft_strdup(op));
		return (parse->i += 2, true);
	}
	if (is_op_char(s[parse->i]))
	{
		add_new_token(&parse->tok, &parse->j, &parse->cap,
			ft_strndup(&s[parse->i], 1));
		return (parse->i += 1, true);
	}
	return (false);
}

static void	parse_word(const char *s, t_parse_state *parse)
{
	size_t	start;
	int		quote;

	start = parse->i;
	quote = 0;
	while (s[parse->i] && (!is_space(s[parse->i]) || quote) && !(!quote
			&& is_op_char(s[parse->i])))
	{
		if (is_quote(s[parse->i]))
		{
			if (!quote)
				quote = s[parse->i];
			else if (quote == s[parse->i])
				quote = 0;
		}
		(parse->i)++;
	}
	add_new_token(&parse->tok, &parse->j, &parse->cap, ft_strndup(s + start,
			parse->i - start));
}

t_token	*shell_split(const char *s)
{
	t_parse_state	parse;

	parse.cap = TOK_INIT_CAP;
	parse.j = 0;
	parse.tok = malloc(sizeof(t_token) * parse.cap);
	if (!parse.tok)
		return (NULL);
	parse.i = 0;
	while (s[parse.i])
	{
		while (is_space(s[parse.i]))
			parse.i++;
		if (!s[parse.i])
			break ;
		if (try_parse_operator(s, &parse))
			continue ;
		parse_word(s, &parse);
	}
	parse.tok[parse.j].value = NULL;
	parse.tok[parse.j].quote = 0;
	return (parse.tok);
}

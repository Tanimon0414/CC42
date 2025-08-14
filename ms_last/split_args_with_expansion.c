/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_with_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:12 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/30 12:51:57 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection_token(const char *token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
	{
		return (true);
	}
	if (ft_isdigit(token[0]) && token[1] == '>')
	{
		return (true);
	}
	return (false);
}

static char	**process_token(t_token token, bool is_export_arg, t_shell *shell)
{
	char	**sub_args;
	char	dummy_quote_type;

	if (token.quote == '\'')
	{
		sub_args = ft_calloc(2, sizeof(char *));
		if (sub_args)
			sub_args[0] = strip_quotes(token.value, &dummy_quote_type);
	}
	else
	{
		sub_args = expand_variables_and_split(token.value, shell,
				is_export_arg);
	}
	return (sub_args);
}

static void	append_sub_args(char **sub, char ***final, int *count,
		int *capacity)
{
	int	old_cap;
	int	k;

	k = 0;
	while (sub[k])
	{
		if (*count >= *capacity - 1)
		{
			old_cap = *capacity;
			*capacity *= 2;
			*final = ft_realloc(*final, old_cap * sizeof(char *), *capacity
					* sizeof(char *));
		}
		(*final)[*count] = ft_strdup(sub[k]);
		(*count)++;
		k++;
	}
}

static char	**build_expanded_args(t_token *tokens, t_shell *shell, int i,
		int args_count)
{
	char	**final_args;
	int		args_cap;
	bool	is_export;
	char	**sub_args;

	args_cap = 16;
	final_args = ft_calloc(args_cap, sizeof(char *));
	is_export = tokens[0].value && ft_strcmp(tokens[0].value, "export") == 0;
	while (tokens[i].value)
	{
		if (is_redirection_token(tokens[i].value))
		{
			i += 2;
			continue ;
		}
		sub_args = process_token(tokens[i], (is_export && i > 0), shell);
		if (sub_args)
		{
			append_sub_args(sub_args, &final_args, &args_count, &args_cap);
			ft_free_split(sub_args);
		}
		i++;
	}
	return (final_args);
}

char	**split_args_with_expansion(const char *cmd, t_shell *shell)
{
	t_token	*tokens;
	char	**final_args;

	tokens = shell_split(cmd);
	if (!tokens)
		return (NULL);
	final_args = build_expanded_args(tokens, shell, 0, 0);
	free_tokens(tokens);
	return (final_args);
}

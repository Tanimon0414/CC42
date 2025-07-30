/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_attachment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:00 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:01 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_expansion(const char *str, size_t *i, char **result,
		t_shell *shell)
{
	char	var_name[256];
	char	*val;
	int		k;

	(*i)++;
	if (str[*i] == '?')
	{
		val = ft_itoa(shell->last_status);
		append_str_to_result(result, val);
		free(val);
		(*i)++;
		return ;
	}
	k = 0;
	ft_bzero(var_name, sizeof(var_name));
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		var_name[k++] = str[(*i)++];
	val = get_env_value(var_name, shell->envp);
	if (val)
		append_str_to_result(result, val);
}

char	*expand_variables_no_quotes(const char *str, t_shell *shell)
{
	char	*result;
	size_t	i;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			handle_expansion(str, &i, &result, shell);
		}
		else
		{
			append_char_to_result(&result, str[i]);
			i++;
		}
	}
	return (result);
}

char	**expand_variables_and_split(const char *str, t_shell *shell,
		int preserve_quotes)
{
	int		should_split;
	char	**final_args;
	char	*expanded_str;
	char	quote_type;

	should_split = contains_unquoted_dollar(str);
	if (preserve_quotes)
	{
		should_split = 0;
	}
	expanded_str = expand_variables(str, shell);
	if (should_split)
	{
		final_args = ft_split(expanded_str, ' ');
	}
	else
	{
		final_args = ft_calloc(2, sizeof(char *));
		if (final_args)
		{
			final_args[0] = strip_quotes(expanded_str, &quote_type);
		}
	}
	free(expanded_str);
	return (final_args);
}

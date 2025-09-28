/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_environmental_variables.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:02 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/30 12:52:03 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_str_to_result(char **result, const char *s)
{
	size_t	old_len;
	size_t	new_len;

	if (!s)
		return ;
	old_len = ft_strlen(*result);
	new_len = old_len + ft_strlen(s);
	*result = ft_realloc(*result, old_len + 1, new_len + 1);
	ft_strcat(*result, (char *)s);
}

void	append_char_to_result(char **result, char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	append_str_to_result(result, s);
}

static void	expand_env_variable(const char *str, size_t *i, char **result,
		t_shell *shell)
{
	char	var_name[256];
	char	*val;
	int		k;

	ft_bzero(var_name, sizeof(var_name));
	k = 0;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		var_name[k++] = str[*i];
		(*i)++;
	}
	val = get_env_value(var_name, shell->envp);
	if (val)
		append_str_to_result(result, val);
}

static void	handle_variable_expansion(const char *str, size_t *i, char **result,
		t_shell *shell)
{
	char	*status_str;

	(*i)++;
	if (str[*i] == '?')
	{
		status_str = ft_itoa(shell->last_status);
		append_str_to_result(result, status_str);
		free(status_str);
		(*i)++;
	}
	else if (!ft_isalpha(str[*i]) && str[*i] != '_')
	{
		append_char_to_result(result, '$');
	}
	else
	{
		expand_env_variable(str, i, result, shell);
	}
}

char	*expand_variables(const char *str, t_shell *shell)
{
	char	*result;
	size_t	i;
	char	quote_state;

	result = ft_calloc(1, 1);
	i = 0;
	quote_state = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			handle_quotes(str[i], &quote_state, &result);
			i++;
		}
		else if (quote_state != '\'' && str[i] == '$')
		{
			handle_variable_expansion(str, &i, &result, shell);
		}
		else
		{
			append_char_to_result(&result, str[i++]);
		}
	}
	return (result);
}

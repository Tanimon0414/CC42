/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:05 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:06 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char c, char *quote_state, char **result)
{
	if (*quote_state == 0)
		*quote_state = c;
	else if (*quote_state == c)
		*quote_state = 0;
	else
		append_char_to_result(result, c);
}

char	*expand_variables_with_control(const char *str, t_shell *shell,
		int preserve_quotes)
{
	char	*expanded;
	char	quote_type;
	char	*stripped;

	expanded = expand_variables(str, shell);
	if (preserve_quotes)
		return (expanded);
	stripped = strip_quotes(expanded, &quote_type);
	free(expanded);
	return (stripped);
}

char	*strip_quotes(const char *str, char *quote_type)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"'
				&& str[len - 1] == '"')))
	{
		*quote_type = str[0];
		return (ft_strndup(str + 1, len - 2));
	}
	else
	{
		*quote_type = 0;
		return (ft_strdup(str));
	}
}

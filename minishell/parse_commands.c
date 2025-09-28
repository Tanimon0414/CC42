/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:57 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:22:58 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe_token(const char *value)
{
	return (ft_strcmp(value, "|") == 0);
}

static int	is_redir_token(const t_token *token)
{
	if (token->quote != 0)
		return (0);
	if (ft_strcmp(token->value, "<") == 0)
		return (1);
	if (ft_strcmp(token->value, ">") == 0)
		return (1);
	if (ft_strcmp(token->value, "<<") == 0)
		return (1);
	if (ft_strcmp(token->value, ">>") == 0)
		return (1);
	return (0);
}

static int	handle_pipe_token(t_cmd **curr_ptr, t_shell *shell)
{
	if (!*curr_ptr || !(*curr_ptr)->args || !(*curr_ptr)->args[0])
	{
		put_error_str("syntax error near unexpected token `|'\n", NULL, NULL);
		shell->last_status = 2;
		return (0);
	}
	*curr_ptr = NULL;
	return (1);
}

static t_cmd	*process_token_loop(t_token *tokens, t_shell *shell,
		t_cmd *head)
{
	t_cmd	*curr;
	t_token	*token_ptr;

	curr = NULL;
	token_ptr = tokens;
	while (token_ptr && token_ptr->value)
	{
		if (!curr)
			curr = create_and_link_cmd(&head);
		if (is_pipe_token(token_ptr->value))
		{
			if (!handle_pipe_token(&curr, shell))
				return (free_cmd_list(head), NULL);
		}
		else if (is_redir_token(token_ptr))
		{
			if (!handle_redir_token(&token_ptr, curr, shell))
				return (free_cmd_list(head), NULL);
		}
		else
			handle_word_token(token_ptr, curr, shell);
		token_ptr++;
	}
	return (head);
}

t_cmd	*parse_commands(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd_head;

	tokens = shell_split(line);
	if (!tokens || !tokens[0].value)
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (!validate_syntax_tokens(tokens, shell))
	{
		free_tokens(tokens);
		return (NULL);
	}
	cmd_head = process_token_loop(tokens, shell, NULL);
	free_tokens(tokens);
	return (cmd_head);
}

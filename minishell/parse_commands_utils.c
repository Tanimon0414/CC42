/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:54 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:11:04 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->has_redir_error = 0;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*create_and_link_cmd(t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*iter;

	new_node = new_cmd_node();
	new_node->args = ft_calloc(1, sizeof(char *));
	if (!*head)
		*head = new_node;
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = new_node;
	}
	return (new_node);
}

int	handle_redir_token(t_token **tokens_ptr, t_cmd *curr, t_shell *shell)
{
	const char	*next_val;
	t_token		*current_token;
	t_token		*next_token;
	int			result;

	current_token = *tokens_ptr;
	next_token = current_token + 1;
	if (!next_token->value || is_operator(next_token->value))
	{
		if (next_token->value)
			next_val = next_token->value;
		else
			next_val = "newline";
		put_error_str("syntax error near unexpected token `", next_val, "'\n");
		shell->last_status = 2;
		return (0);
	}
	result = parse_redirection_token(current_token, next_token, curr, shell);
	if (result == 0)
		return (0);
	*tokens_ptr = next_token;
	return (1);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

void	handle_word_token(t_token *token, t_cmd *curr, t_shell *shell)
{
	char	**expanded_args;
	int		j;

	expanded_args = expand_variables_and_split(token->value, shell, 0);
	if (expanded_args)
	{
		j = 0;
		while (expanded_args[j])
		{
			add_arg_to_cmd(curr, expanded_args[j]);
			j++;
		}
		ft_free_split(expanded_args);
	}
}

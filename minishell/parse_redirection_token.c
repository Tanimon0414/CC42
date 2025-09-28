/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:03 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:10:39 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_path(t_token *file_tok, t_token *op_token,
		t_shell *shell)
{
	if (ft_strcmp(op_token->value, "<<") == 0 || file_tok->quote == '\'')
		return (ft_strdup(file_tok->value));
	return (expand_variables(file_tok->value, shell));
}

static int	open_redir_file(const char *op, const char *path, t_shell *shell)
{
	if (ft_strcmp(op, "<") == 0)
		return (open(path, O_RDONLY));
	if (ft_strcmp(op, ">") == 0)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (ft_strcmp(op, ">>") == 0)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (ft_strcmp(op, "<<") == 0)
		return (setup_heredoc((char *)path, shell));
	return (-1);
}

static void	handle_redir_error(const char *path, t_cmd *cmd)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		put_error_str((char *)path, ": Is a directory\n", NULL);
	else
		perror(path);
	cmd->has_redir_error = 1;
}

static void	handle_fd_redirection(const char *op, const char *path, t_cmd *cmd)
{
	int	target_fd;
	int	fd;

	target_fd = op[0] - '0';
	if (op[2] == '>')
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		handle_redir_error(path, cmd);
		return ;
	}
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		cmd->has_redir_error = 1;
	}
	close(fd);
}

int	parse_redirection_token(t_token *op, t_token *file, t_cmd *cmd,
		t_shell *shell)
{
	char	*path;
	int		fd;

	if (cmd->has_redir_error || !op || !file || !file->value)
		return (1);
	path = get_expanded_path(file, op, shell);
	if (!path)
		return (1);
	if (ft_isdigit(op->value[0]) && op->value[1] == '>')
	{
		handle_fd_redirection(op->value, path, cmd);
		free(path);
		return (1);
	}
	fd = open_redir_file(op->value, path, shell);
	if (fd == -1)
	{
		if (ft_strcmp(op->value, "<<") == 0)
			return (free(path), 0);
		handle_redir_error(path, cmd);
	}
	else
		assign_fd_to_cmd(fd, op->value, cmd);
	free(path);
	return (1);
}

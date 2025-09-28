/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:21:54 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/29 14:08:44 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"));
}

static void	parent_process_routine(t_cmd *cmd, int *prev_fd, int pfd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pfd[1]);
		*prev_fd = pfd[0];
	}
}

static void	child_process_routine(t_cmd *cmd, t_shell *shell, int prev_fd,
		int pfd[2])
{
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (cmd->next)
		dup2(pfd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
	execute_cmd(cmd, shell);
}

pid_t	execute_pipeline_loop(t_cmd *cmds, t_shell *shell, int prev_fd,
		pid_t last_pid)
{
	t_cmd	*cur;
	int		pipefd[2];

	cur = cmds;
	while (cur)
	{
		if (cur->next && pipe(pipefd) == -1)
			return (perror("pipe"), -1);
		last_pid = fork();
		if (last_pid == -1)
			return (perror("fork"), -1);
		if (last_pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (cur->has_redir_error)
				exit(1);
			child_process_routine(cur, shell, prev_fd, pipefd);
		}
		parent_process_routine(cur, &prev_fd, pipefd);
		cur = cur->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (last_pid);
}

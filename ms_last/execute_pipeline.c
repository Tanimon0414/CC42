/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:21:57 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:58:39 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_redir_errors(t_cmd *cmds, int devnull)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (cur->has_redir_error)
		{
			if (cur->infile == -1)
				cur->infile = devnull;
			if (cur->outfile == -1)
				cur->outfile = STDOUT_FILENO;
			if (cur->args)
			{
				ft_free_split(cur->args);
				cur->args = ft_calloc(1, sizeof(char *));
			}
		}
		cur = cur->next;
	}
}

static void	wait_for_pipeline(pid_t last_pid, t_shell *shell)
{
	int	status;

	if (last_pid == -1)
	{
		shell->last_status = 1;
		return ;
	}
	if (waitpid(last_pid, &status, 0) == -1)
		perror("waitpid");
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
	}
}

static void	execute_fork_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		devnull;
	pid_t	last_pid;

	devnull = open("/dev/null", O_RDONLY);
	if (devnull == -1)
	{
		perror("open /dev/null");
		return ;
	}
	prepare_redir_errors(cmds, devnull);
	setup_signals_non_interactive();
	last_pid = execute_pipeline_loop(cmds, shell, -1, -1);
	wait_for_pipeline(last_pid, shell);
	close(devnull);
}

static void	run_parent_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->has_redir_error)
		shell->last_status = 1;
	else
	{
		if (cmd->infile != STDIN_FILENO)
		{
			dup2(cmd->infile, STDIN_FILENO);
			close(cmd->infile);
		}
		if (cmd->outfile != STDOUT_FILENO)
		{
			dup2(cmd->outfile, STDOUT_FILENO);
			close(cmd->outfile);
		}
		shell->last_status = execute_builtin(cmd->args, shell);
	}
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	execute_pipeline(char *line, t_shell *shell)
{
	t_cmd	*cmds;

	cmds = parse_commands(line, shell);
	if (!cmds)
		return ;
	if (ft_strcmp(line, "exit \"\"") == 0 || ft_strcmp(line, "exit \'\'") == 0)
	{
		put_error_str("exit: : numeric argument required", NULL, NULL);
		free_envp(shell->envp);
		exit(2);
	}
	if (!cmds->next && cmds->args && cmds->args[0]
		&& is_parent_builtin(cmds->args[0]))
	{
		run_parent_builtin(cmds, shell);
	}
	else
	{
		execute_fork_pipeline(cmds, shell);
	}
	free_cmd_list(cmds);
}

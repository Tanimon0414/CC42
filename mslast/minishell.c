/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:48 by kkuramot          #+#    #+#             */
/*   Updated: 2025/08/02 14:08:43 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_unclosed_quotes(char **line_ptr)
{
	char	*newline;

	while (is_unclosed_quote(*line_ptr))
	{
		newline = readline("> ");
		if (!newline)
			return (1);
		*line_ptr = join_lines_for_quotes(*line_ptr, newline);
		if (!*line_ptr)
			return (1);
	}
	return (0);
}

static char	*read_full_command(t_shell *shell)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		write(1, "exit\n", 5);
		free_envp(shell->envp);
		exit(shell->last_status);
	}
	if (handle_unclosed_quotes(&line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	handle_pre_execution_checks(char *line, t_shell *shell)
{
	char	*error_arg;
	char	*msg;

	if (is_empty_or_whitespace(line))
		return (1);
	if (is_quoted_whitespace(line))
	{
		error_arg = strip_quotes(line, &line[0]);
		put_error_str(error_arg, ": command not found\n", NULL);
		free(error_arg);
		shell->last_status = 127;
		return (1);
	}
	if (ft_strncmp(line, "\'\'", 2) == 0 || ft_strncmp(line, "\"\"", 2) == 0)
	{
		msg = "\"\"";
		if (ft_strncmp(line, "\'\'", 2) == 0)
			msg = "\"\"";
		put_error_str(msg, ": command not found\n", NULL);
		shell->last_status = 127;
		return (1);
	}
	return (0);
}

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals_interactive(shell);
		line = read_full_command(shell);
		if (g_signal_status == 130)
		{
			shell->last_status = 130;
			g_signal_status = 0;
		}
		if (!line)
			continue ;
		if (handle_pre_execution_checks(line, shell))
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		line = expand_tilde_in_line(line, shell);
		execute_pipeline(line, shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	main_loop(&shell);
	free_envp(shell.envp);
	return (shell.last_status);
}

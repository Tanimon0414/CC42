/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:37 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/29 14:07:21 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_rand(int max)
{
	static unsigned int	lcg_seed = 123456789;

	lcg_seed = (lcg_seed * 1103515245 + 12345) % 0x7FFFFFFF;
	return (lcg_seed % max);
}

static int	create_heredoc_filepath(char *path_buffer)
{
	char	*rand_str;

	rand_str = ft_itoa(my_rand(2147483647));
	if (!rand_str)
		return (-1);
	ft_strcpy(path_buffer, "/tmp/minishell_heredoc_");
	ft_strcat(path_buffer, rand_str);
	free(rand_str);
	return (0);
}

static void	heredoc_child_process(const char *filepath, const char *limiter,
		t_shell *shell)
{
	int		fd;
	char	*line;
	char	*expanded;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, shell);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(line);
	}
	close(fd);
	exit(0);
}

int	setup_heredoc(char *limiter, t_shell *shell)
{
	char	tmp_file[1024];
	pid_t	pid;
	int		status;
	int		read_fd;

	if (create_heredoc_filepath(tmp_file) != 0)
		return (-1);
	setup_signals_non_interactive();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		heredoc_child_process(tmp_file, limiter, shell);
	waitpid(pid, &status, 0);
	setup_signals_interactive(shell);
	if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		unlink(tmp_file);
		return (write(STDOUT_FILENO, "\n", 1), -1);
	}
	read_fd = open(tmp_file, O_RDONLY);
	if (read_fd >= 0)
		unlink(tmp_file);
	return (read_fd);
}

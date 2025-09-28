/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_token_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:23:00 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/27 18:23:01 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_fd_to_cmd(int fd, const char *op, t_cmd *cmd)
{
	if (op[0] == '<')
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		cmd->infile = fd;
	}
	else
	{
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		cmd->outfile = fd;
	}
}

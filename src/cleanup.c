/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:18:47 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/27 15:18:50 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int prev_pipe, int fd_in, int fd_out)
{
	if (prev_pipe != fd_in && prev_pipe != -1)
		close(prev_pipe);
	if (fd_in != -1)
		close(fd_in);
	close(fd_out);
}

void	cleanup_and_exit(t_content *content, int fd_in, int fd_out,
		int exit_code)
{
	if (content)
		free_content(content);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	exit(exit_code);
}

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

void	child_cleanup(t_content *cmd, int *pipes, int prev_pipe, int fd_out)
{
	if (cmd->next)
		close_pipes(pipes);
	if (prev_pipe != -1)
		close(prev_pipe);
	close(fd_out);
	free_content(cmd);
	exit(EXIT_FAILURE);
}

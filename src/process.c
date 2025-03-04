/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:07:46 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/27 15:07:49 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child(t_content *cmd, int *pipes, int prev_pipe, int fd_out)
{
	dup2(prev_pipe, STDIN_FILENO);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd->next)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close_pipes(pipes);
	}
	else
	{
		dup2(fd_out, STDOUT_FILENO);
		if (pipes[0] != -1)
			close_pipes(pipes);
	}
	close(fd_out);
}

void	process_parent(t_content *cmd, int *pipes, int *prev_pipe, int fd_in)
{
	if (*prev_pipe != fd_in && *prev_pipe != -1)
		close(*prev_pipe);
	if (cmd->next)
	{
		*prev_pipe = pipes[0];
		close(pipes[1]);
	}
}

int	wait_processes(t_content *head)
{
	t_content	*cmd;
	int			status;

	cmd = head;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (!cmd->next && WIFEXITED(status))
			return (WEXITSTATUS(status));
		cmd = cmd->next;
	}
	return (1);
}

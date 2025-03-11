/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:43:48 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/18 18:43:49 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_content *cmd, int fd_in, int fd_out, char **envp)
{
	int			pipes[2];
	int			prev_pipe;
	t_content	*head;

	prev_pipe = fd_in;
	head = cmd;
	while (cmd)
	{
		init_pipe(cmd, pipes, fd_in, fd_out);
		if (cmd->pid == 0)
		{
			if (prev_pipe == -1 && cmd == head)
				child_cleanup(cmd, pipes, prev_pipe, fd_out);
			process_child(cmd, pipes, prev_pipe, fd_out);
			execve(cmd->cmd_path, cmd->args, envp);
			perror(cmd->args[0]);
			child_cleanup(cmd, pipes, prev_pipe, fd_out);
		}
		else
		{
			process_parent(cmd, pipes, &prev_pipe, fd_in);
			cmd = cmd->next;
		}
	}
	close_fds(prev_pipe, fd_in, fd_out);
	return (wait_processes(head));
}

static t_content	*get_content(char **av, int ac, char **envp)
{
	t_content	*content;

	if (!ft_strcmp(av[1], "here_doc"))
		content = init_content(ac - 4, av + 3, envp);
	else
		content = init_content(ac - 3, av + 2, envp);
	return (content);
}

int	main(int ac, char **av, char **envp)
{
	t_content	*content;
	int			fd_in;
	int			fd_out;
	int			exit_status;

	if (!envp || !envp[0] || ac < 5)
		exit(EXIT_FAILURE);
	if (!ft_strcmp(av[1], "here_doc"))
		init_heredoc(av, ac, &fd_in, &fd_out);
	else
		init_files(av, ac, &fd_in, &fd_out);
	content = get_content(av, ac, envp);
	if (!content)
	{
		perror("cmd error :");
		cleanup_and_exit(NULL, fd_in, fd_out, 127);
	}
	exit_status = pipex(content, fd_in, fd_out, envp);
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
		exit_status = 1;
	cleanup_and_exit(content, fd_in, fd_out, exit_status);
	return (exit_status);
}

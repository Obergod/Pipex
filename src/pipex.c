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

static void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

static void	child_cleanup(t_content *cmd, int *pipes, int prev_pipe, int fd_out)
{
	if (cmd->next)
		close_pipes(pipes);
	if (prev_pipe != -1)
		close(prev_pipe);
	close(fd_out);
	free_content(cmd);
	exit(EXIT_FAILURE);
}

int	pipex(t_content *cmd, int fd_in, int fd_out, char **envp)
{
	int			pipes[2];
	int			prev_pipe;
	t_content	*head;
	int			status;

	prev_pipe = fd_in;
	head = cmd;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipes) == -1)
				cleanup_and_exit(cmd, fd_in, fd_out, 1);
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			if (cmd->next)
				close_pipes(pipes);
			perror("Fork failed");
			exit(1);
		}
		else if (cmd->pid == 0)
		{
			if (prev_pipe == -1 && cmd == head)
				child_cleanup(cmd, pipes, prev_pipe, fd_out);
			dup2(prev_pipe, STDIN_FILENO);
			if (prev_pipe != -1)
				close(prev_pipe);
			if (cmd->next)
			{
				dup2(pipes[1], STDOUT_FILENO);
				close_pipes(pipes);
			}
			else
				dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			execve(cmd->cmd_path, cmd->args, envp);
			perror("Command execution failed");
			child_cleanup(cmd, pipes, prev_pipe, fd_out);
		}
		else
		{
			if (prev_pipe != fd_in && prev_pipe != -1)
				close(prev_pipe);
			if (cmd->next)
			{
				prev_pipe = pipes[0];
				close(pipes[1]);
			}
			cmd = cmd->next;
		}
	}
	if (prev_pipe != fd_in && prev_pipe != -1)
		close(prev_pipe);
	if (fd_in != -1)
		close(fd_in);
	close(fd_out);
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

int	main(int ac, char **av, char **envp)
{
	t_content	*content;
	int			fd_in;
	int			fd_out;
	int			exit_status;

	if (ac < 5)
		exit(EXIT_FAILURE);
	if (!ft_strcmp(av[1], "here_doc"))
	{
		if (ac < 6)
			exit(EXIT_FAILURE);
		if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
			perror("Output file error");
		fd_in = here_doc(av[2]);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		check_files_acess(av[1], av[ac - 1], &ac);
		fd_in = open(av[1], O_RDONLY);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (!ft_strcmp(av[1], "here_doc"))
		content = init_content(ac - 4, av + 3, envp);
	else
		content = init_content(ac - 3, av + 2, envp);
	if (!content)
	{
		perror("cmd error :");
		cleanup_and_exit(NULL, fd_in, fd_out, 127);
	}
	exit_status = pipex(content, fd_in, fd_out, envp);
	cleanup_and_exit(content, fd_in, fd_out, exit_status);
	return (exit_status);
}

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
/*
void	parent_process()
{

}

void	child_process(int f1, )
{


}

*/
void	pipex(t_content *cmd, int fd_in, int fd_out, char **envp)
{
	int			pipes[2];
	int 		prev_pipe;
	t_content	*head;
	/*pid = malloc(sizeof(pid_t) * nb_cmd);
	if (!pid)
		return ;*/
	/*if (fd_in < 0 || fd_out < 0)
		return (exit);*/
	prev_pipe = fd_in;
	head = cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipes);
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			if (cmd->next)
			{
				close(pipes[1]);
				close(pipes[0]);
			}
			perror("OMG NO\n");
			exit(1);
		}
		else if (cmd->pid == 0)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
			if (cmd->next)
			{
				dup2(pipes[1], STDOUT_FILENO);
				close(pipes[1]);
				close(pipes[0]);
			}
			else
				dup2(fd_out, STDOUT_FILENO);
			execve(cmd->cmd_path, cmd->args, envp);
			perror("Child Process failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_pipe != fd_in)
				close(prev_pipe);
			if (cmd->next)
			{
				prev_pipe = pipes[0];
				close(pipes[1]);
			}
		}
	}
	cmd = head;
	while(cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	if (prev_pipe != fd_in)
		close(prev_pipe);
	close(fd_in);
	close(fd_out);
}
int	main(int ac, char **av, char **envp)
{
	t_content	*content;
	int			fd_in;
	int			fd_out;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror("Input File error");
		exit(EXIT_FAILURE);
	}
	fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		close(fd_in);
		perror("Output File error");
		exit(EXIT_FAILURE);
	}
	content = init_content(ac, av, envp);
	pipex(content, fd_in, fd_out, envp);
	close(fd_in);
	close(fd_out);
	return (0);
	/*printf("cmd : %s\n", content->args[0]);
	printf("cmd_path : %s\n", content->cmd_path);
	//execve(content->cmd_path, content->args, NULL);
	content = content->next;
	printf("cmd : %s\n", content->args[0]);
	printf("cmd_path : %s\n", content->cmd_path);
	//execve(content->cmd_path, content->args, NULL);*/
}

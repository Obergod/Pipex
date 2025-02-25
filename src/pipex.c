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
			cmd = cmd->next;
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

	if (ac < 5)
		exit(EXIT_FAILURE);
	if (!ft_strcmp(av[1], "here_doc"))
	{
		if (ac < 6)
			exit(EXIT_FAILURE);
		if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
		{
			perror("Output file error");
			exit(EXIT_FAILURE);
		}
		fd_in = here_doc(av[2]);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		check_files_acess(av[1], av[ac - 1], &ac, &av);
		fd_in = open(av[1], O_RDONLY);
		fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	/*	if (fd_in < 0 || fd_out < 0)
		{
			if (fd_in >= 0)
				close(fd_in);
			perror("File error");
			exit(EXIT_FAILURE);
		}*/
	if (!ft_strcmp(av[1], "here_doc"))
		content = init_content(ac - 4, av + 3, envp);
	else
		content = init_content(ac - 3, av + 2, envp);
	pipex(content, fd_in, fd_out, envp);
	free_content(content);
	close(fd_in);
	close(fd_out);
	/*while (content)
	{
	printf("cmd : %s\n", content->args[0]);
	printf("cmd_path : %s\n", content->cmd_path);
	execve(content->cmd_path, content->args, envp);
	content = content->next;
	}
	printf("cmd : %s\n", content->args[0]);
	printf("cmd_path : %s\n", content->cmd_path);
	//execve(content->cmd_path, content->args, NULL);*/
	return (0);
}

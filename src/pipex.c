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

void	parent_process()
{

}

void	child_process(int f1, )
{


}

t_cmd	*get_cmd(int ac, char **av)
{

	//parse to get all cmd (strlen for malloc ?)
	//get_all_file etc...
}

void	pipex(t_content *cmd, int fd_in, int fd_out, int nb_cmd)
{
	pid_t	pid; //pointeur ?
	int		pipes[2];
	int		i;
	int 	prev_pipe;
	/*pid = malloc(sizeof(pid_t) * nb_cmd);
	if (!pid)
		return ;*/
	if (!data || !data->cmd_list || input_fd < 0 || output_fd < 0)
		return (handle_error());
	i = 0;
	prev_pipe = fd_in;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipes);
		pid = fork();
		if (pid < 0)
		{
			perror("OMG NO\n");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(prev_pipe, STDIN_FILENO);
			if (cmd->next)
				dup2(pipes[1], STDOUT_FILENO);
			else
				dup2(fd_out, STDOUT_FILENO);
		}
		execve(cmd->cmd_path, cmd->args, NULL);
		else
		{
			if (i == 1)
				close(prev_pipe);
			if (cmd->next)
			{
				prev_pipe = pipes[0];
			}
			close(pipes[1]);
		}
		cmd = cmd->next;
		i = 1;
	}
		//need to find a way to link in and out. dup2 ?
}
	// need to use execv linked to the cmds
int	main(int ac, char **av, char **envp)
{
	while(envp[i])
	{
		strcmp(envp[i], "PATH=", 5)
			char *paths = split(envp[i], ":");
	}
}

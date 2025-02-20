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
	pid_t	*pid;
	int		pipes[2];
	int		i;
	int 	*prev_pipe; //pointeur ?

	i = 0;
	pid = malloc(sizeof(pid_t) * nb_cmd);
	if (!pid)
		return ;
	prev_pipe = fd_in;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipes);

		pid[i++] = fork();
		if (pid < 0)
		{
			//free pipes and pid
			perror("OMG NO\n");
			exit(1);
		}
		if (pid == 0)
		{
			dup2(prev_pipe, STDIN_FILENO);
			printf("child process\n");
		}
		else
		{
			printf("parrent process\n");
		}
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

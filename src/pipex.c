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
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->wc_cmd = ac - 3;
	//parse to get all cmd (strlen for malloc ?)
	//get_all_file etc...
}

void	pipex(int f1, int f2, int nb_cmd)
{
	int	*pipes[2];
	pid_t	*pid;
	int		i;

	i = -1;
	pid = malloc(sizeof(pid_t) * nb_cmd);
	if (!pid)
		return ;
	pipes = malloc(sizeof(int *) * nb_cmd - 1);
	if (!pipes)
	{
		free(pid);
		return ;
	}
	while (++i < nb_cmd - 1)
		pipe(pipes[i]);
	i = -1;
	while (++i < nb_cmd)
	{
		pid[i] = fork();
		if (pid < 0)
		{
			//free pipes and pid
			return (perror("OMG NO\n"));
		}
		//need to find a way to link in and out. dup2 ?
	}
	// need to use execv linked to the cmds
	if (pid == 0)
	{
		printf("child process\n");
	}
	else
	{
		printf("parrent process\n");
	}
}

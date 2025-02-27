/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:49 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/27 15:49:50 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_heredoc(char **av, int ac, int *fd_in, int *fd_out)
{
	if (ac < 6)
		exit(EXIT_FAILURE);
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
		perror("Output file error");
	*fd_in = here_doc(av[2]);
	*fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	init_files(char **av, int ac, int *fd_in, int *fd_out)
{
	check_files_acess(av[1], av[ac - 1], &ac);
	*fd_in = open(av[1], O_RDONLY);
	*fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int	init_pipe(t_content *cmd, int *pipes, int fd_in, int fd_out)
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
	return (0);
}

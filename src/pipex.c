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

void	pipex(int f1, int f2)
{
	int	end[2];
	pid_t	pid;

	pipe(end);
	pid = fork();
	if (pid < 0)
		return (perror("OMG NO\n"));

}

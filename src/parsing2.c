/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:38:13 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/24 19:38:14 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	no_here_doc(char *limiter)
{
	char	*line;
	int		pipes[2];
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_next_line(STDIN_FILENO);
		/*if (!line)
			return ;*/
		if (line == NULL)
		{
			i = 1;
			free(line);
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write (pipes[1], line, ft_strlen(line));
		free(line);
	}
	close(pipes[1]);
	if (i == 1)
	{
		close(pipes[0]);
		exit(EXIT_FAILURE);
	}
}

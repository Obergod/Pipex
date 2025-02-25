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

int	here_doc(char *limiter)
{
	char	*line;
	int		pipes[2];

	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		exit(EXIT_FAILURE);
	if (pipe(pipes) == -1)
	{
		free(limiter);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(limiter);
			close(pipes[1]);
			return (pipes[0]);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(limiter);
			break ;
		}
		write (pipes[1], line, ft_strlen(line));
		free(line);
	}
	close(pipes[1]);
	free(line);
	return (pipes[0]);
}

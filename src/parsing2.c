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

int	check_files_acess(char *infile, char *outfile, int *ac)
{
	if (access(infile, F_OK | R_OK) == -1)
	{
		perror("Input file error");
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Output file error");
		*ac -= 1;
	}
	return (1);
}

static void	handle_line(char *line, char *limiter, int *pipes)
{
	if (!line)
	{
		free(limiter);
		close(pipes[1]);
		return ;
	}
	if (!ft_strcmp(line, limiter))
	{
		free(line);
		return ;
	}
	write(pipes[1], line, ft_strlen(line));
	free(line);
}

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
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		handle_line(line, limiter, pipes);
		if (!line || !ft_strcmp(line, limiter))
			break ;
	}
	free(limiter);
	close(pipes[1]);
	return (pipes[0]);
}

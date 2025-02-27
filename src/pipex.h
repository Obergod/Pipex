/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:01:56 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/20 14:02:01 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include "libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
//# include "ft_printf.h"

typedef struct s_content
{
	char				**args;
	char				*cmd_path;
	pid_t				pid;
	struct s_content	*next;
}						t_content;

/*****		A trier		******/

/*****		parsing		******/
char		*get_cmd_path(char **envp, char *cmd);
int			check_files_acess(char *infile, char *outfile, int *ac);
t_content	*create_node(char *cmd_str, char **envp);
t_content	*init_content(int nb_cmd, char **av, char **envp);
void		free_content(t_content *head);
int			here_doc(char *limiter);

/****		process		******/
void		process_child(t_content *cmd, int *pipes, int prev_pipe,
				int fd_out);
void		process_parent(t_content *cmd, int *pipes, int *prev_pipe,
				int fd_in);
int			wait_processes(t_content *head);

/***		cleanup		*****/
void		cleanup_and_exit(t_content *content, int fd_in, int fd_out,
				int exit_code);
void		close_pipes(int *pipes);
void		child_cleanup(t_content *cmd, int *pipes, int prev_pipe,
				int fd_out);
void		close_fds(int prev_pipe, int fd_in, int fd_out);

/***		inits		*****/
void		init_heredoc(char **av, int ac, int *fd_in, int *fd_out);
void		init_files(char **av, int ac, int *fd_in, int *fd_out);
int			init_pipe(t_content *cmd, int *pipes, int fd_in, int fd_out);

#endif

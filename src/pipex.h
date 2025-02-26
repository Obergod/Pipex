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
char					*get_cmd_path(char **envp, char *cmd);
int						check_files_acess(char *infile, char *outfile, int *ac);
t_content				*create_node(char *cmd_str, char **envp);
t_content				*init_content(int nb_cmd, char **av, char **envp);
void					free_content(t_content *head);
int						here_doc(char *limiter);

#endif

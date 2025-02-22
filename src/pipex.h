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

# include <unistd.h>
# include <stdlib.h>
 #include <sys/wait.h>

# include "libft.h"

typedef struct s_content {
    char **args;
    char *cmd_path;
    struct s_content *next;
	pid_t	pid;
} t_content;


/*****		A trier		******/

/*****		parsing		******/
char		*get_cmd_path(char **envp, char *cmd);
static int	check_files(char *infile, char *outfile);
t_content	*create_node(char *cmd_str, char **envp);
t_content 	*init_content(int ac, char **av, char **envp);
void		free_content(t_content *head);





#endif 

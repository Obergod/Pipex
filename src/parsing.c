/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:02:40 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/20 14:02:53 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char **envp, char *cmd)
{
	int		i;
	char	**cmd_path;
	char	*tmp;
	char *full_path;

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
		{
			cmd_path = ft_split(envp[i] + 5, ':');
			if (!cmd_path)
				return (NULL);
			break ;
		}
	if (strncmp(envp[i], "PATH=", 5))
		exit(EXIT_FAILURE);
	i = -1;
	while (cmd_path[++i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_split(cmd_path);
			return (full_path);
		}
		free(full_path);
	}
	return (NULL);
}

int    check_files_acess(char *infile, char *outfile, int *ac, char ***av)
{
    if (access(infile, F_OK | R_OK) == -1)
    {
        perror("Input file error");
		*ac -= 1;
		*av += 1;
    }
    if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
    {
        perror("Output file error");
        *ac -= 1;
    }
    return (1);
}

t_content *create_node(char *cmd_str, char **envp)
{
	t_content	*node;

	node = malloc(sizeof(t_content));
	if (!node)
		return (NULL);
	node->args = ft_split(cmd_str, ' ');
	if (!node->args)
	{
		free_content(node);
		return (NULL);
	}
	node->cmd_path = get_cmd_path(envp, node->args[0]);
	if (!node->cmd_path)
	{
		ft_free_split(node->args);
		return (NULL);
	}
	node->next = NULL;
	node->pid = 0;
	return (node);	
}

void	free_content(t_content *head)
{
	t_content *temp;

	while (head)
	{
		temp = head->next;
		if (head->args)
			ft_free_split(head->args);
		if (head->cmd_path)
			free(head->cmd_path);
		free(head);
		head = temp;
	}
}

t_content *init_content(int nb_cmd, char **av, char **envp)
{
	int	i;
	t_content *head;
	t_content *temp;

	i = 0;
	head = create_node(av[i], envp);
	if (!head)
		exit (EXIT_FAILURE);
	temp = head;
	while (++i < nb_cmd)
	{
		temp->next = create_node(av[i], envp);
		if (!temp->next)
		{
			free_content(head);
			exit (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (head);
}

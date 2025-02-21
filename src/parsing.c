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
	char	*temp;
	char *full_path

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
		{
			cmd_path = split(envp[i] + 5, ":");
			break ;
		}
	if (!cmd_path)
		return (NULL);
	i = -1;
	while (cmd_path[++i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static int    check_files(char *infile, char *outfile)
{
    if (access(infile, F_OK | R_OK) == -1)
    {
        perror("Input file error");
        exit (EXIT_FAILURE);
    }
    if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
    {
        perror("Output file error");
        exit (EXIT_FAILURE);
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
		free_split(node->args);
		return (NULL);
	}
	node->next = NULL;
	pid = 0;
	return (node);	
}

void	free_content(t_content *head)
{
	t_content *temp;

	while (head)
	{
		temp = head->next;
		if (head->args)
			free_split(head->args);
		if (head->cmd_path)
			free(head->cmd_path);
		free(head);
		head = temp;
	}
}

t_content *init_content(char **evnp, char **av, int ac)
{
	int	i;
	t_content *head;
	t_content *temp;

	i = 2;
	check_files(av[1], av[ac - 1]);
	head = create_node(av[i]);
	if (!head)
		exit (EXIT_FAILURE);
	temp = head;
	while (++i < ac - 1)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/16 15:31:55 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// renvoie le fd du fichier en fonction de l'operateur de redirection

int	count_redir(char **tokens)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!tokens)
		return (res);
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			res++;
		i++;
	}
	return (res);
}

int get_fd(char *operator, char *file_name)
{
	int		fd;

	fd = -1;
	if (access(file_name, W_OK) == 0 || access(file_name, F_OK) == -1)
	{
		if (!ft_strcmp(operator, ">"))
			fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (!ft_strcmp(operator, ">>"))
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (!ft_strcmp(operator, "<"))
			fd = open(file_name, O_RDONLY);
		else if (!ft_strcmp(operator, "<<"))
			printf("work in progress\n");
	}
	return (fd);
}

int open_fd(char **tokens, t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->d.n_redir = count_redir(tokens);
	if (cmd->d.n_redir == 0)
		return (0);
	cmd->d.opened_fd = ft_calloc(cmd->d.n_redir, sizeof(t_redir));
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			cmd->d.opened_fd[j].fd = get_fd(tokens[i], tokens[i + 1]);
			if (tokens[i][0] == '>')
				cmd->d.opened_fd[j].is_outfile = 1;
			else
				cmd->d.opened_fd[j].is_outfile = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int	assign_fd(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->d.n_redir)
	{
		if (cmd->d.opened_fd->is_outfile)
			cmd->fd_out = cmd->d.opened_fd[i].fd;
		else
			cmd->fd_in = cmd->d.opened_fd[i].fd;
		i++;
	}
	return (1);
}

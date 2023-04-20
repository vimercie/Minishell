/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:14:30 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 21:31:55 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}

int	close_files(t_command *cmd)
{
	int	i;

	i = cmd->d.n_redir - 1;
	while (i >= 0)
	{
		if (cmd->d.files[i].fd > 2 && find_duplicate(i, cmd->d.files) == -1)
		{
			if (close(cmd->d.files[i].fd) == -1)
				return (print_bash_error("close", 1));
		}
		i--;
	}
	i = 0;
	while (i < cmd->d.n_redir)
	{
		free(cmd->d.files[i].file_name);
		i++;
	}
	return (1);
}

void	free_loop(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (!data->cmd)
			return ;
		while (i < data->n_cmd)
		{
			free(data->cmd[i].pathname);
			free_tab(data->cmd[i].argv);
			close_files(&data->cmd[i]);
			if (data->cmd[i].d.files)
				free(data->cmd[i].d.files);
			i++;
		}
		free(data->cmd);
	}
}

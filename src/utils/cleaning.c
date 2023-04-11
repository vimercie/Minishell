/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:14:30 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/11 14:12:02 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_files(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->d.n_redir)
	{
		if (!close(cmd->d.files[i].fd))
			return (0);
		free(cmd->d.files[i].file_name);
		i++;
	}
	return (1);
}

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
			free(data->cmd[i].d.files);
			i++;
		}
		free(data->cmd);
	}
}

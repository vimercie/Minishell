/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:14:30 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/08 02:20:43 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	close_pipes(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->n_cmd)
// 	{
// 		if (data->cmd[i].d.pipefd[0] > 2
// 			|| data->cmd[i].d.pipefd[1] > 2)
// 		{
// 			close(data->cmd[i].d.pipefd[0]);
// 			close(data->cmd[i].d.pipefd[1]);
// 			printf("closed pipe[0] = %d\n", data->cmd[i].d.pipefd[0]);
// 			printf("closed pipe[1] = %d\n", data->cmd[i].d.pipefd[1]);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

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

void	free_memory(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data)
	{
		if (!data->cmd)
			return ;
		while (i < data->n_cmd)
		{
			j = 0;
			free_tab(data->cmd[i].argv);
			while (j < data->cmd[i].d.n_redir)
			{
				if (data->cmd[i].d.files[j].fd > 2
					&& (data->cmd[i].d.files[j].fd != data->cmd[i].fd_in
					&& data->cmd[i].d.files[j].fd != data->cmd[i].fd_out))
				{
					close(data->cmd[i].d.files[j].fd);
					printf("closed fd = %d\n", data->cmd[i].d.files[j].fd);
				}
				free(data->cmd[i].d.files[j].file_name);
				j++;
			}
			free(data->cmd[i].d.files);
			free(data->cmd[i].pathname);
			i++;
		}
		free(data->cmd);
	}
}

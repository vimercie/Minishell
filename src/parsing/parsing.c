/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/28 16:28:45 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		data->cmd[i].fd_in = 0;
		data->cmd[i].fd_out = 1;
		if (i < data->n_cmd - 1)
			pipe(data->cmd[i].d.pipefd);
		if (i != 0)
		{
			if (data->cmd[i].fd_in > 2)
			{
				printf("closed fd_in = %d\n", data->cmd[i].fd_in);
				close(data->cmd[i].fd_in);
			}
			data->cmd[i].fd_in = data->cmd[i - 1].d.pipefd[0];
		}
		if (i < data->n_cmd - 1)
		{
			if (data->cmd[i].fd_out > 2)
			{
				printf("closed fd_out = %d\n", data->cmd[i].fd_out);
				close(data->cmd[i].fd_out);
			}
			data->cmd[i].fd_out = data->cmd[i].d.pipefd[1];
		}
		i++;
	}
	return (1);
}

int	parsing(char *input, t_data *data)
{
	char	**pipe_split;
	int		i;

	i = 0;
	data->n_cmd = cmd_count(input, '|');
	data->cmd = ft_calloc(data->n_cmd, sizeof(t_command));
	pipe_split = custom_split(input, '|', data->n_cmd);
	pipe_init(data);
	while (i < data->n_cmd)
	{
		data->cmd[i].d.id = i + 1;
		cmd_init(pipe_split[i], &data->cmd[i]);
		redirect_fd(pipe_split[i], &data->cmd[i]);
		i++;
	}
	free_tab(pipe_split);
	return (1);
}

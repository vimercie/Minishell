/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:41:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/12 19:50:54 by vimercie         ###   ########lyon.fr   */
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
		if (i > 0)
		{
			if (pipe(data->cmd[i].d.pipefd) == -1)
				return (0);
			data->cmd[i - 1].fd_out = data->cmd[i].d.pipefd[1];
			data->cmd[i].fd_in = data->cmd[i].d.pipefd[0];
		}
		i++;
	}
	return (1);
}

int	set_redirection(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->d.n_redir)
	{
		if (cmd->d.files[i].fd == -1)
			return (print_linux_error(cmd->d.files[i].file_name, 2));
		if (cmd->d.files[i].is_outfile)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			cmd->fd_out = cmd->d.files[i].fd;
		}
		else
		{
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			cmd->fd_in = cmd->d.files[i].fd;
		}
		i++;
	}
	return (1);
}

int	set_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		set_redirection(&data->cmd[i]);
		i++;
	}
	return (1);
}
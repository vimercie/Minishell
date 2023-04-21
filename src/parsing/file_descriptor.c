/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:41:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/21 02:43:08 by vimercie         ###   ########lyon.fr   */
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
		{
			if (cmd->d.files[i].is_heredoc == 0)
				print_linux_error(cmd->d.files[i].file_name);
			return (0);
		}
		if (cmd->d.files[i].is_outfile > 0)
			cmd->fd_out = cmd->d.files[i].fd;
		else
			cmd->fd_in = cmd->d.files[i].fd;
		i++;
	}
	return (1);
}

int	set_fd(t_data *data)
{
	int	return_val;
	int	i;

	i = 0;
	return_val = 1;
	while (i < data->n_cmd)
	{
		if (!set_redirection(&data->cmd[i]))
			return_val = 0;
		i++;
	}
	return (return_val);
}

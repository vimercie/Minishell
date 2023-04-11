/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/04 17:45:00 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (i > 0)
		{
			if (pipe(data->cmd[i].d.pipefd) == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	set_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (i > 0)
		{
			data->cmd[i].fd_in = data->cmd[i].d.pipefd[0];
			data->cmd[i - 1].fd_out = data->cmd[i].d.pipefd[1];
		}
		i++;
	}
	return (1);
}

int	set_fd(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	set_pipe(data);
	while (i < data->n_cmd)
	{
		j = 0;
		while (j < data->cmd[i].d.n_redir)
		{
			if (data->cmd[i].d.files[j].fd == -1)
			{
				print_linux_error(data->cmd[i].d.files[j].file_name, 2);
				return (0);
			}
			if (data->cmd[i].d.files[j].is_outfile == 0)
				data->cmd[i].fd_in = data->cmd[i].d.files[j].fd;
			else
				data->cmd[i].fd_out = data->cmd[i].d.files[j].fd;
			j++;
		}
		i++;
	}
	return (1);
}

int	data_init(char *input, t_data *data)
{
	data->n_cmd = count_cmd(input);
	if (data->n_cmd > 0)
		data->cmd = ft_calloc(data->n_cmd, sizeof(t_command));
	if (!data->cmd)
		return (0);
	return (1);
}

int	parsing(char *input, t_data *data)
{
	char	**pipe_split;
	char	**tokens;
	int		i;

	i = 0;
	data->cmd = NULL;
	if (!check_syntax(input))
		return (0);
	if (!data_init(input, data))
		return (0);
	if (!pipe_init(data))
		return (0);
	pipe_split = ft_split(input, '|');
	if (!pipe_split)
		return (0);
	while (i < data->n_cmd)
	{
		tokens = tokenize_input(pipe_split[i]);
		cmd_init(tokens, &data->cmd[i], data);
		free_tab(tokens);
		i++;
	}
	free_tab(pipe_split);
	if (!set_fd(data))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/23 16:28:02 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	prompt_join(char *cmd_line)
{
	char	*buffer;
	char	*tmp;

	while (is_prompt(cmd_line))
	{
		tmp = ft_strjoin(cmd_line, "\n");
		free(cmd_line);
		buffer = readline("> ");
		cmd_line = ft_strjoin(tmp, buffer);
		free(buffer);
		free(tmp);
	}
	return (1);
}

int	pipe_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (i < data->n_cmd - 1)
		{
			pipe(data->cmd[i].d.pipefd);
			printf("pipefd[1] = %d\n\n", data->cmd[i].d.pipefd[1]);
			printf("pipefd[0] = %d\n", data->cmd[i].d.pipefd[0]);
		}
		if (i != 0)
			data->cmd[i].fd_in = data->cmd[i - 1].d.pipefd[0];
		if (i < data->n_cmd - 1)
			data->cmd[i].fd_out = data->cmd[i].d.pipefd[1];
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
	while (i < data->n_cmd)
	{
		data->cmd[i].data = data;
		data->cmd[i].d.id = i + 1;
		cmd_init(pipe_split[i], &data->cmd[i]);
		i++;
	}
	pipe_init(data);
	return (1);
}

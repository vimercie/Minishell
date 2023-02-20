/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/20 15:04:32 by vimercie         ###   ########lyon.fr   */
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

int	parsing(t_data *data, char *input)
{
	char	**pipe_split;
	int		i;

	i = 0;
	data->n_cmd = cmd_count(input, '|');
	data->cmd = ft_calloc(data->n_cmd + 1, sizeof(t_command));
	pipe_split = custom_split(input, '|', data->n_cmd);
	while (i < data->n_cmd)
	{
		data->cmd[i].data = data;
		data->cmd[i].fd_in = 0;
		data->cmd[i].fd_out = 1;
		redirect_fd(pipe_split[i], &data->cmd[i]);
		cmd_tab_init(pipe_split[i], &data->cmd[i]);
		i++;
	}
	return (1);
}

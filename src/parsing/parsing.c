/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/23 15:11:00 by vimercie         ###   ########lyon.fr   */
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
	return (1);
}

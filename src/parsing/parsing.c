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
			pipe(data->cmd[i].d.pipefd);
			data->cmd[i].fd_in = data->cmd[i].d.pipefd[0];
			data->cmd[i - 1].fd_out = data->cmd[i].d.pipefd[1];
		}
		i++;
	}
	return (1);
}

int	data_init(char *input, t_data *data)
{
	data->cmd = NULL;
	data->n_cmd = count_cmd(input);
	if (data->n_cmd == 0)
		return (0);
	if (check_syntax(input))
		data->cmd = ft_calloc(data->n_cmd, sizeof(t_command));
	if (!data->cmd)
		return (0);
	return (1);
}

int	parsing(char *input, t_data *data)
{
	char	**pipe_split;
	char	**tokens;
	int		return_val;
	int		i;

	i = 0;
	return_val = 1;
	if (!data_init(input, data))
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
	pipe_init(data);
	return (return_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/09 19:11:31 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fd_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		data->cmd[i].fd_in = 0;
		data->cmd[i].fd_out = 1;
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

int	parsing(char *input, t_data *data)
{
	char	**pipe_split;
	char	**tokens;
	int		i;

	i = 0;
	data->n_cmd = cmd_count(input, '|');
	data->cmd = ft_calloc(data->n_cmd, sizeof(t_command));
	pipe_split = ft_split(input, '|');
	fd_init(data);
	while (i < data->n_cmd)
	{
		tokens = tokenize_input(pipe_split[i]);
		cmd_init(tokens, &data->cmd[i], data->env);
		free_tab(tokens);
		i++;
	}
	free_tab(pipe_split);
	return (1);
}

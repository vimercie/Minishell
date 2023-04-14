/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/14 17:07:46 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int		err_return;
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
		err_return = cmd_init(tokens, &data->cmd[i], data);
		free_tab(tokens);
		i++;
	}
	free_tab(pipe_split);
	if (!err_return)
		return (0);
	if (!set_fd(data))
		return (0);
	return (1);
}

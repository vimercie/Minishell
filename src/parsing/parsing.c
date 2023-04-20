/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 18:01:29 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	data_init(char **tokens, t_data *data)
{
	data->n_cmd = count_cmd(tokens);
	if (data->n_cmd > 0)
		data->cmd = ft_calloc(data->n_cmd, sizeof(t_command));
	if (!data->cmd)
		return (0);
	return (1);
}

int	cmd_init_loop(char **tokens, t_data *data)
{
	char	**cmd_split;
	int		return_val;
	int		token_i;
	int		i;

	i = 0;
	token_i = 0;
	return_val = 0;
	while (i < data->n_cmd)
	{
		cmd_split = cmd_pipe_split(tokens + token_i, &token_i, &data->cmd[i]);
		return_val = cmd_init(cmd_split, &data->cmd[i], data);
		free_tab(cmd_split);
		i++;
		token_i++;
	}
	return (return_val);
}

int	parsing(char *input, t_data *data)
{
	char	**tokens;
	int		return_val;

	data->cmd = NULL;
	tokens = tokenize_input(input);
	if (!tokens)
		return (0);
	if (!check_syntax(input, tokens))
		return (0);
	if (!data_init(tokens, data))
		return (0);
	if (!pipe_init(data))
		return (0);
	return_val = cmd_init_loop(tokens, data);
	free_tab(tokens);
	if (!return_val || !set_fd(data))
		return (0);
	return (1);
}

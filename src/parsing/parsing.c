/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 17:46:09 by vimercie         ###   ########lyon.fr   */
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

int	count_args(char **tokens)
{
	int	n_arg;

	n_arg = 0;
	if (!tokens)
		return (0);
	while (tokens[n_arg])
	{
		if (ft_strcmp(tokens[n_arg], "|") == 0)
			return (n_arg);
		n_arg++;
	}
	return (n_arg);
}

char	**token_pipe_split(char **tokens, int *token_i, t_command *cmd)
{
	char	**res;
	int		i;

	i = 0;
	cmd->d.n_arg = count_args(tokens);
	res = ft_calloc(cmd->d.n_arg + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (i < cmd->d.n_arg)
	{
		res[i] = ft_strdup(tokens[i]);
		i++;
	}
	*token_i += i;
	return (res);
}

int	parsing(char *input, t_data *data)
{
	char	**tokens;
	char	**pipe_split;
	int		err_return;
	int		i;
	int		j;

	i = 0;
	j = 0;
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
	while (i < data->n_cmd)
	{
		pipe_split = token_pipe_split(tokens + j, &j, &data->cmd[i]);
		err_return = cmd_init(pipe_split, &data->cmd[i], data);
		free_tab(pipe_split);
		j++;
		i++;
	}
	free_tab(tokens);
	if (!err_return || !set_fd(data))
		return (0);
	return (1);
}

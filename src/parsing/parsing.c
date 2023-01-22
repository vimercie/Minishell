/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/22 06:31:12 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*prompt_join(char *input)
{
	char	*res;
	char	*buffer;
	char	*tmp;

	res = ft_strdup(input);
	while (is_prompt(res))
	{
		tmp = ft_strjoin(res, "\n");
		free(res);
		buffer = readline("> ");
		res = ft_strjoin(tmp, buffer);
		free(buffer);
		free(tmp);
	}
	return (res);
}

t_data	*parsing(char *input)
{
	t_data		*data;
	char		**pipe_split;
	char		*cmd;

	if (!input[0])
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	cmd = prompt_join(input);
	cmd = syntax_cleaner(cmd);
	// cmd = redirect_fd(cmd);
	// cmd = replace_env_v(cmd);
	data->n_cmd = cmd_count(cmd, '|');
	pipe_split = custom_split(cmd, '|', data->n_cmd);
	data->cmd = cmd_tab_init(pipe_split, data->n_cmd);
	// data->cmd = redirect_fd(data->cmd, data->n_cmd);
	free(cmd);
	free_tab(pipe_split);
	return (data);
}

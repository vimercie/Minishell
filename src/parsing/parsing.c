/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/04 19:55:15 by vimercie         ###   ########.fr       */
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
		tmp = ft_strdup(res);
		free(res);
		buffer = readline("pipe> ");
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
	char		*clean_input;
	char		*full_input;

	if (!input[0])
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	full_input = prompt_join(input);
	clean_input = syntax_cleaner(full_input);
	// full_input = replace_env_v(clean_input);
	data->n_cmd = cmd_count(clean_input, '|');
	pipe_split = custom_split(clean_input, '|', data->n_cmd);
	data->cmd = cmd_tab_init(pipe_split, data->n_cmd);
	free(full_input);
	free(clean_input);
	free(pipe_split);
	return (data);
}

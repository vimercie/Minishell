/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/28 17:23:01 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*prompt_join(char *input)
// {
// 	char	*res;
// 	char	*buffer;
// 	int		is_prompt;
// 	int		i;

// 	i = 0;
// 	is_prompt = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '|' && !is_command(input + i))
// 			is_prompt = 1;
// 	}
// 	while (is_prompt = 1)
// 	{
		
// 	}
// }

t_data	*parsing(char *input)
{
	t_data		*data;
	char		**pipe_split;
	char		*clean_input;

	if (!input[0])
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	// input = prompt_join(input);
	// input = replace_env_v(input);
	clean_input = syntax_cleaner(input);
	data->n_cmd = cmd_count(input, '|');
	pipe_split = custom_split(input, '|', data->n_cmd);
	data->cmd = cmd_tab_init(pipe_split, data->n_cmd);
	free(clean_input);
	free(pipe_split);
	return (data);
}

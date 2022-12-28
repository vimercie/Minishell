/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 23:23:24 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*manage_quote(char *input, int *i, int *j)
{
	int	index;

	index = *i + 1;
	while (input[index] != input[*i] && input[index])
		index++;
	if (input[index] == input[*i]
		&& index != *i + 1
		&& input[index])
	{
		while (*i <= index)
		{
			input[*j] = input[*i];
			*i += 1;
			*j += 1;
		}
	}
	else
		*i += 1;
	return (input);
}

char	*skip_ws(char *input, int *i, int *j)
{
	int	ws;
	int	start_i;

	ws = 0;
	start_i = *i;
	while (is_ws(input + *i))
	{
		ws = 1;
		*i += 1;
	}
	if (ws == 1 && start_i != 0 && input[*i])
	{
		input[*j] = ' ';
		*j += 1;
	}
	return (input);
}

char	*syntax_cleaner(char *input)
{
	char	*res;
	int		res_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_quote(input + i))
			input = manage_quote(input, &i, &j);
		else if (is_ws(input + i))
			input = skip_ws(input, &i, &j);
		else
		{
			input[j] = input[i];
			i++;
			j++;
		}
	}
	input[j] = '\0';
	res_len = ft_strlen(input);
	if (res_len == 0)
		return (NULL);
	res = ft_calloc(res_len + 1, sizeof(char));
	ft_strlcpy(res, input, res_len + 1);
	return (res);
}

t_command	*parsing(char *input)
{
	t_command	*cmd;
	char		**pipe_split;
	char		*clean_input;
	int			n_cmd;

	if (!input[0])
		return (NULL);
	// clean_input = replace_env_v(clean_input);
	clean_input = syntax_cleaner(input);
	n_cmd = cmd_count(input, '|');
	pipe_split = custom_split(input, '|', n_cmd);
	cmd = data_init(pipe_split, n_cmd);
	free(clean_input);
	free(pipe_split);
	return (cmd);
}

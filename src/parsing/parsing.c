/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/19 19:22:51 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*manage_quote(char *input, int *i, int *j)
{
	int	index;

	index = *i + 1;
	while (input[index] != input[*i] && input[index])
		index++;
	if (input[index] == input[*i] && index != *i + 1 && input[index])
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

char	*skip_junk(char *input, int *i, int *j)
{
	int	ws;
	int	start_i;

	ws = 0;
	start_i = *i;
	while (is_junk(input + *i))
	{
		if (input[*i] == ' ' && ws == 0)
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
		if (is_junk(input + i))
			input = skip_junk(input, &i, &j);
		else if (is_quote(input + i))
			input = manage_quote(input, &i, &j);
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
	int			n_pipes;

	n_pipes = count_pipes(input);
	pipe_split = ft_split(input, '|');
	cmd = data_init(pipe_split, n_pipes);
	free_tab(pipe_split);
	// cmd = replace_env_v(cmd);
	return (cmd);
}

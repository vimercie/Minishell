/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/17 05:32:57 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*manage_quote(char *input, char *res, int *i, int *j)
{
	int	index;

	index = *i + 1;
	while (input[index] != input[*i] && input[index])
		index++;
	if (input[index] == input[*i] && index != *i + 1 && input[index])
	{
		while (*i <= index)
		{
			res[*j] = input[*i];
			*i += 1;
			*j += 1;
		}
	}
	else
		*i += 1;
	return (res);
}

char	*skip_junk(char *input, char *res, int *i, int *j)
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
		res[*j] = ' ';
		*j += 1;
	}
	return (res);
}

char	*input_cleaner(char *input)
{
	char	*res;
	int		i;
	int		j;

	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_junk(input + i))
			res = skip_junk(input, res, &i, &j);
		else if (is_quote(input + i))
			res = manage_quote(input, res, &i, &j);
		else
		{
			res[j] = input[i];
			i++;
			j++;
		}
	}
	free(input);
	return (res);
}

// char	*replace_env_v(char *cmd)
// {
// 	char	*var;
// 	int		i;

// 	i = 0;
// 	return (cmd);
// }

t_command	**parsing(char *input)
{
	t_command	**cmd;

	cmd = cmd_init(input);
	if (cmd == NULL)
		return (0);
	// cmd = replace_env_v(cmd);
	free(input);
	return (cmd);
}

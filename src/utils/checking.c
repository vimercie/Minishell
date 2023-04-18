/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:02:24 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/18 17:12:41 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_pipe(int fd, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (fd == data->cmd[i].d.pipefd[0]
			|| fd == data->cmd[i].d.pipefd[1])
			return (1);
		i++;
	}
	return (0);
}

int	is_quote(char *s, int index)
{
	if (!s || !s[index])
		return (0);
	if ((s[index] == '\"' || s[index] == '\'')
		&& !is_quoted(s, index)
		&& ((is_quoted(s, index + 1) || is_quoted(s, index - 1))
			|| (s[index + 1] == s[index] || s[index - 1] == s[index])))
	{
		if (s[index] == '\'')
			return (1);
		else
			return (2);
	}
	return (0);
}

int	is_quoted(char *s, int index)
{
	int	opening_quote_index;
	int	i;

	i = 0;
	while (s[i])
	{
		opening_quote_index = i;
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			while (s[i] != s[opening_quote_index] && s[i])
				i++;
			if ((index > opening_quote_index && index < i)
				&& (s[i] == s[opening_quote_index] && s[i]))
			{
				if (s[opening_quote_index] == '\'')
					return (1);
				return (2);
			}
		}
		i++;
	}
	return (0);
}

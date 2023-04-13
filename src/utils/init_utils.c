/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:54:47 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/11 14:12:05 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(char **tokens)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!tokens)
		return (res);
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (tokens[i + 1])
				i++;
		}
		else
			res++;
		i++;
	}
	return (res);
}

int	count_redir(char **tokens)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!tokens)
		return (res);
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			res++;
		i++;
	}
	return (res);
}

int	count_cmd(char *s)
{
	int		i;
	int		res;

	if (!s[0])
		return (0);
	i = 0;
	res = 1;
	while (s[i])
	{
		if (s[i] == '|'
			&& s[i + 1] != '|'
			&& s[i - 1] != '|')
		{
			if (is_string_blank((s + i) + 1))
				return (res);
			res++;
		}
		i++;
	}
	return (res);
}

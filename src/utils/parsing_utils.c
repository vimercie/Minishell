/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/20 23:01:37 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_redir(char **tokens)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
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

	if (!s)
		return (0);
	i = 0;
	res = 1;
	while (s[i])
	{
		if (s[i] == '|'
			&& s[i + 1] != '|'
			&& s[i - 1] != '|')
		{
			if(is_string_blank((s + i) + 1))
				return (res);
			res++;
		}
		i++;
	}
	return (res);
}

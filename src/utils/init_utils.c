/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:54:47 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 21:24:53 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_quotes(char *s)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (is_quote(s, i) > 0)
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

int	count_cmd(char **tokens)
{
	int		i;
	int		res;

	if (!tokens)
		return (0);
	i = 0;
	res = 1;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (is_string_blank(tokens[i + 1]))
				return (res);
			res++;
		}
		i++;
	}
	return (res);
}

int	count_token_args(char **tokens)
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

int	count_args(char **tokens)
{
	int	n_arg;
	int	i;

	i = 0;
	n_arg = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			return (n_arg);
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
			n_arg++;
		i++;
	}
	return (n_arg);
}

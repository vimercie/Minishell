/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:54:47 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/09 19:24:24 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*gather_full_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (full_path);
}

char	*remove_quotes(char *s)
{
	char	*res;
	int		n_quote;
	int		i;
	int		j;

	i = 0;
	n_quote = 0;
	while (s[i])
	{
		if (is_quote(s, i))
			n_quote++;
		i++;
	}
	res = ft_calloc(i - n_quote + 1, sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!is_quote(s, i))
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	free(s);
	return (res);
}

int		count_arg(char **tokens)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
			res++;
		i++;
	}
	return (res);
}

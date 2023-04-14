/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/14 15:56:13 by vimercie         ###   ########lyon.fr   */
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

	if (!s)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	n_quote = 0;
	while (s[i])
	{
		if (is_quote(s, i) > 0)
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

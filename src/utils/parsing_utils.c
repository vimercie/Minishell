/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/18 15:03:20 by vimercie         ###   ########lyon.fr   */
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
	int		i;
	int		j;

	if (!s)
	{
		free(s);
		return (NULL);
	}
	if (count_quotes(s) == 0)
		return (s);
	i = 0;
	j = 0;
	res = ft_calloc(i - count_quotes(s) + 1, sizeof(char));
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

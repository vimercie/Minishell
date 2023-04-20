/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 17:59:17 by vimercie         ###   ########lyon.fr   */
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
	res = ft_calloc(ft_strlen(s) - count_quotes(s) + 1, sizeof(char));
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

char	**cmd_pipe_split(char **tokens, int *token_i, t_command *cmd)
{
	char	**res;
	int		i;

	i = 0;
	cmd->d.n_arg = count_args(tokens);
	res = ft_calloc(cmd->d.n_arg + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (i < cmd->d.n_arg)
	{
		res[i] = ft_strdup(tokens[i]);
		i++;
	}
	*token_i += i;
	return (res);
}

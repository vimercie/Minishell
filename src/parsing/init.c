/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/06 16:28:53 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_cmd_path(char *cmd)
{
	char	**path;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!cmd)
		return (res);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		res = gather_full_path(path[i], cmd);
		if (access(res, X_OK) == 0)
			break ;
		free(res);
		i++;
	}
	if (!path[i])
		res = ft_strdup(cmd);
	free(path);
	return (res);
}

char	**argv_init(char **tokens)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(get_n_arg(tokens) + 1, sizeof(char *));
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
		{
			res[j] = ft_strdup(tokens[i]);
			j++;
		}
		i++;
	}
	return (res);
}

void	cmd_init(char **tokens, t_command *cmd)
{
	cmd->d.n_arg = get_n_arg(tokens);
	cmd->argv = argv_init(tokens);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	open_fd(tokens, cmd);
	assign_fd(cmd);
	return ;
}

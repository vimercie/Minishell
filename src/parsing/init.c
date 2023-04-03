/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/03 18:28:16 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_fd(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->d.n_redir)
	{
		if (cmd->d.files[i].is_outfile == 0)
			cmd->fd_in = cmd->d.files[i].fd;
		else
			cmd->fd_out = cmd->d.files[i].fd;
		i++;
	}
	return ;
}

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
	free_tab(path);
	return (res);
}

char	**argv_init(char **tokens, t_env *env)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(count_args(tokens) + 1, sizeof(char *));
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
		{
			res[j] = replace_env_var(tokens[i], env);
			j++;
		}
		i++;
	}
	return (res);
}

void	cmd_init(char **tokens, t_command *cmd, t_data *data)
{
	set_fd(cmd);
	cmd->d.n_arg = count_args(tokens);
	cmd->argv = argv_init(tokens, data->env);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	cmd->d.n_redir = count_redir(tokens);
	cmd->d.files = files_init(tokens, cmd->d.n_redir, data);
	return ;
}

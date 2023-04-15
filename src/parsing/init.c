/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/15 19:11:27 by vimercie         ###   ########lyon.fr   */
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
		return (NULL);
	if (is_directory(cmd))
	{
		print_bash_error(cmd, 126);
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		res = gather_full_path(path[i], cmd);
		if (access(res, X_OK) == 0)
			break ;
		free(res);
		i++;
	}
	if (!path[i])
		res = NULL;
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
			res[j] = handle_env_var(tokens[i], env);
			res[j] = remove_quotes(res[j]);
			j++;
		}
		i++;
	}
	return (res);
}

int	cmd_init(char **tokens, t_command *cmd, t_data *data)
{
	cmd->argv = argv_init(tokens, data->env);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	cmd->d.n_arg = count_args(tokens);
	cmd->d.n_redir = count_redir(tokens);
	cmd->d.files = files_init(tokens, cmd->d.n_redir, data);
	cmd->d.is_builtin = is_builtin(cmd->argv[0]);
	if (!is_builtin(cmd->argv[0]) && !cmd->pathname)
		return (print_bash_error(cmd->argv[0], 127));
	return (1);
}

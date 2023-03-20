/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/20 23:48:51 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_file_table	*files_init(char **tokens, int n_redir)
{
	t_file_table	*files;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!tokens || n_redir == 0)
		return (NULL);
	files = ft_calloc(n_redir + 1, sizeof(t_file_table));
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			files[j].file_name = ft_strdup(tokens[i + 1]);
			files[j].fd = get_fd(tokens[i], tokens[i + 1]);
			files[j].is_outfile = 0;
			if (tokens[i][0] == '>')
				files[j].is_outfile = 1;
			j++;
		}
		i++;
	}
	return (files);
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
			i++;
		else
		{
			if (ft_strchr(tokens[i], '$') != NULL)
				res[j] = replace_env_var(tokens[i], env);
			else
				res[j] = ft_strdup(tokens[i]);
			j++;
		}
		i++;
	}
	return (res);
}

void	cmd_init(char **tokens, t_command *cmd, t_env *env)
{
	cmd->d.n_arg = count_args(tokens);
	cmd->d.n_redir = count_redir(tokens);
	cmd->d.files = files_init(tokens, cmd->d.n_redir);
	cmd->argv = argv_init(tokens, env);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	return ;
}

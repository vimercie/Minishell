/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/16 13:42:36 by vimercie         ###   ########.fr       */
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

char	*get_cmd_path(char *cmd)
{
	char	**path;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
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

char	**argv_init(char *input)
{
	char	**res;
	int	    n_arg;
	int     arg_len;
	int     i;

	i = 0;
	n_arg = get_n_arg(input);
	res = ft_calloc(n_arg + 1, sizeof(char *));
	if (!input[0])
		res[0] = ft_calloc(1, sizeof(char));
	while (input[0])
	{
		while (ft_isspace(input[0]) && input[0])
			input++;
		if (!input[0])
			break ;
		arg_len = 0;
		while ((!ft_isspace(input[arg_len]) || is_in_quotes(input, arg_len))
			&& input[arg_len])
			arg_len++;
		res[i] = ft_substr(input, 0, arg_len);
		res[i] = remove_quotes(res[i]);
		i++;
		input += arg_len;
	}
	return (res);
}

void	cmd_tab_init(char *input, t_data *data)
{
	char		**pipe_split;
	int			i;

	i = 0;
	data->n_cmd = cmd_count(input, '|');
	data->cmd = ft_calloc(data->n_cmd + 1, sizeof(t_command));
	pipe_split = custom_split(input, '|', data->n_cmd);
	while (i < data->n_cmd)
	{
		data->cmd[i].argv = argv_init(pipe_split[i]);
		data->cmd[i].pathname = get_cmd_path(data->cmd[i].argv[0]);
		data->cmd[i].fd_in = 0;
		data->cmd[i].fd_out = 1;
		i++;
	}
	free_tab(pipe_split);
	return ;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/20 15:03:50 by vimercie         ###   ########lyon.fr   */
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
	if (!cmd[0])
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

void	argv_init(char *input, t_command *cmd)
{
	int     arg_len;
	int     i;

	i = 0;
	cmd->n_arg = get_n_arg(input);
	if (!is_command(input))
	{
		cmd->argv = ft_calloc(1, sizeof(char *));
		cmd->argv[0] = ft_calloc(1, sizeof(char));
		return ;
	}
	cmd->argv = ft_calloc(cmd->n_arg, sizeof(char *));
	while (is_command(input))
	{
		while (ft_isspace(input[0]) && input[0])
			input++;
		arg_len = 0;
		while ((!ft_isspace(input[arg_len]) || is_in_quotes(input, arg_len))
			&& input[arg_len])
			arg_len++;
		cmd->argv[i] = ft_strndup(input, arg_len);
		cmd->argv[i] = remove_quotes(cmd->argv[i]);
		i++;
		input += arg_len;
	}
	return ;
}

void	cmd_tab_init(char *input, t_command *cmd)
{
	argv_init(input, cmd);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	return ;
}
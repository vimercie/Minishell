/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/23 02:57:51 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		**path_init(void)
{
	char	**path_array;
	char	*path_start;

	path_array = ft_split(getenv("PATH"), ':');
	path_start = ft_substr(path_array[0], 5, ft_strlen(path_array[0]));
	free(path_array[0]);
	path_array[0] = NULL;
	path_array[0] = ft_strdup(path_start);
	return (path_array);
}

char		*cmd_init(char *input)
{
	char	*path;
	char	**path_array;
	int		i;

	i = 0;
	path_array = path_init();
	path = gather_full_path(path_array[i], input);
	while (access(path, X_OK) == -1 && path_array[i])
	{
		i++;
		free(path);
		path = gather_full_path(path_array[i], input);
	}
	if (!path_array[i] && access(path, X_OK) == -1)
		path = ft_strdup(input);
	return (path);
}

char	**args_init(char *input)
{
	char	**res;
	int	    n_arg;
	int     arg_len;
	int     i;

	i = 0;
	n_arg = get_n_arg(input);
	res = ft_calloc(n_arg + 1, sizeof(char *));
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

t_command	*cmd_tab_init(char **pipe_split, int n_cmd)
{
	t_command	*cmd;
	int			i;

	i = 0;
	if (pipe_split == NULL)
		return (NULL);
	cmd = ft_calloc(n_cmd + 1, sizeof(t_command));
	while (i < n_cmd)
	{
		cmd[i].args = args_init(pipe_split[i]);
		cmd[i].cmd = cmd_init(cmd[i].args[0]);
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		i++;
	}
	cmd[i].cmd = NULL;
	return (cmd);
}
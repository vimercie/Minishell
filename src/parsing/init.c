/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 17:47:25 by vimercie         ###   ########.fr       */
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
	path_array[0] = ft_strdup(path_start);
	return (path_array);
}

char		*cmd_init(char *input)
{
	char	*path;
	char	**path_array;
	int		i;

	if (input == NULL)
		return (NULL);
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

	if (input == NULL)
		return (NULL);
	i = 0;
	n_arg = get_n_arg(input);
	res = malloc((n_arg + 1) * sizeof(char *));
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
	res[i] = NULL;
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
		data->cmd[i].args = args_init(pipe_split[i]);
		data->cmd[i].cmd = cmd_init(data->cmd[i].args[0]);
		data->cmd[i].fd_in = 0;
		data->cmd[i].fd_out = 1;
		i++;
	}
	data->cmd[i].cmd = NULL;
	free_tab(pipe_split);
	return ;
}
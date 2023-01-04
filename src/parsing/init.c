/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/04 19:21:45 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_end_index(char *input)
{
	int		in_quotes;
	int		i;

	i = 0;
	in_quotes = 0;
	while (input[i])
	{
		if (is_quote(input + i))
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else
				in_quotes = 0;
		}
		if ((is_ws(input + i) || input[i] == '|') && in_quotes == 0)
			return (i);
		i++;
	}
	return (i);
}

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
	int		n_cmd;
	int		i;
	int		j;

	i = 0;
	n_cmd = 0;
	while (input[i])
	{
		i += cmd_end_index(input + i);
		i++;
		n_cmd++;
	}
	res = ft_calloc(n_cmd + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (input[j] && is_command(input + j))
	{
		while (is_ws(input + j))
			j++;
		res[i] = ft_substr(input, j, cmd_end_index(input + j));
		res[i] = remove_quotes(res[i]);
		j += cmd_end_index(input + j);
		i++;
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
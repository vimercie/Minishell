/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 04:34:05 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipes(char *input)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (is_command(input + i + 1))
				res++;
			else
				printf("readline = %s\n", readline("pipe> "));
		}
		i++;
	}
	return (res);
}

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
		if (is_ws(input + i) && in_quotes == 0)
			return (i);
		i++;
	}
	return (i);
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
	while (input[j])
	{
		while (is_junk(input + j))
			j++;
		res[i] = ft_substr(input, j, cmd_end_index(input + j));
		j += cmd_end_index(input + j);
		i++;
	}
	return (res);
}

char		*cmd_init(char *input)
{
	char	*path;
	char	*path_start;
	char	**path_array;
	int		i;

	path_array = ft_split(getenv("PATH"), ':');
	path_start = ft_substr(path_array[0], 5, ft_strlen(path_array[0]));
	free(path_array[0]);
	path_array[0] = ft_strdup(path_start);
	free(path_start);
	i = 0;
	path = gather_full_path(path_array[i], input);
	while (access(path, X_OK) == -1 && path_array[i])
	{
		i++;
		free(path);
		path = gather_full_path(path_array[i], input);
	}
	if (!path_array[i])
		path = NULL;
	return (path);
}

t_command	*data_init(char **pipe_split, int n_pipes)
{
	t_command	*cmd;
	int			i;

	i = 0;
	if (pipe_split == NULL)
		return (NULL);
	cmd = ft_calloc(n_pipes + 2, sizeof(t_command));
	while (i < n_pipes + 1)
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
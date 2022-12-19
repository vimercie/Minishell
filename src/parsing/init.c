/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/19 22:02:59 by vimercie         ###   ########.fr       */
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

char	**args_init(char *cmd)
{
	char	**cmd_split;
	char	**res;
	int		n_ws;
	int		i;

	i = 0;
	n_ws = 0;
	cmd_split = ft_split(cmd, ' ');
	while (cmd_split[n_ws])
		n_ws++;
	i = 0;
	res = ft_calloc(n_ws + 1, sizeof(char *));
	while (cmd_split[i])
	{
		res[i - 1] = ft_strdup(cmd_split[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char		*cmd_init(char *input)
{
	char	*res;
	int		i;

	i = 0;
	while (input[i] != ' ' && input[i])
		i++;
	res = ft_substr(input, 0, i);
	return (res);
}

t_command	*data_init(char **pipe_split, int n_pipes)
{
	t_command	*cmd;
	char		*clean_input;
	int			i;

	i = 0;
	cmd = ft_calloc(n_pipes + 2, sizeof(t_command));
	while (i < n_pipes + 1)
	{
		clean_input = syntax_cleaner(pipe_split[i]);
		// clean_input = replace_env_v(cmd);
		if (clean_input == NULL)
		{
			free(cmd);
			return (NULL);
		}
		cmd[i].cmd = cmd_init(clean_input);
		cmd[i].args = args_init(clean_input);
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		i++;
	}
	free(clean_input);
	cmd[i].cmd = NULL;
	return (cmd);
}
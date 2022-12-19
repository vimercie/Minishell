/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/19 17:49:45 by vimercie         ###   ########.fr       */
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
			res++;
		i++;
	}
	return (res);
}

char	**args_init(char **cmd_split)
{
	char	**res;
	int		wc;
	int		i;

	wc = 0;
	while (cmd_split[wc])
		wc++;
	res = ft_calloc(wc + 1, sizeof(char *));
	i = 1;
	if (!cmd_split[i])
		res = NULL;
	while (cmd_split[i])
	{
		res[i - 1] = ft_strdup(cmd_split[i]);
		cmd_split += 1;
		i++;
	}
	return (res);
}

t_command	*cmd_init(char **pipe_split, int n_pipes)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = ft_calloc((n_pipes + 2), sizeof(t_command));
	while (i < n_pipes + 1)
	{
		cmd[i].cmd = input_cleaner(pipe_split[i]);
		cmd[i].args = NULL;
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 0;
		i++;
	}
	cmd[i].cmd = NULL;
	return (cmd);
}
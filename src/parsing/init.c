/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/17 05:36:08 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	free_array_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i]);
	free(tab);
	return (0);
}

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
		printf("res[%d - 1] = %s\n", i, res[i - 1]);
		cmd_split += 1;
		i++;
	}
	return (res);
}

t_command	**cmd_init(char *input)
{
	t_command	**cmd;
	char		**cmd_split;
	char		**pipe_split;
	int			n_pipes;

	pipe_split = ft_split(input, '|');
	if (pipe_split == NULL)
		return (NULL);
	n_pipes = count_pipes(input);
	cmd = malloc(n_pipes * sizeof(t_command));
	while (n_pipes >= 0)
	{
		cmd_split = ft_split(pipe_split[n_pipes], ' ');
		cmd_split[n_pipes] = input_cleaner(pipe_split[n_pipes]);
		cmd[n_pipes]->cmd = ft_strdup(cmd_split[0]);
		printf("cmd[%d]->cmd #1= %s\n", n_pipes, cmd[n_pipes]->cmd);
		cmd[n_pipes]->args = args_init(cmd_split);
		printf("cmd[%d]->cmd #2= %s\n", n_pipes, cmd[n_pipes]->cmd);
		cmd[n_pipes]->fd_in = 0;
		cmd[n_pipes]->fd_out = 0;
		free(cmd_split[n_pipes]);
		n_pipes--;
	}
	free(cmd_split);
	return (cmd);
}
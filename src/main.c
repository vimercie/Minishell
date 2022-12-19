/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/19 19:01:48 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}

int	free_cmd(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].cmd)
	{
		j = 0;
		free(cmd[i].cmd);
		while (cmd[i].args[j])
		{
			free(cmd[i].args[j]);
			cmd[i].args[j] = NULL;
			j++;
		}
		cmd[i].cmd = NULL;
		i++;
	}
	free(cmd);
	return (0);
}

int	main(void)
{
	t_command	*cmd;
	char		*buffer;
	int			i;
	int			j;

	while (1)
	{
		i = 0;
		buffer = readline("GigaBash$ ");
		cmd = parsing(buffer);
		free(buffer);
		while (cmd[i].cmd)
		{
			j = 0;
			printf("cmd[%d].cmd = %s\n", i, cmd[i].cmd);
			while (cmd[i].args[j])
			{
				printf("cmd[%d].args[%d] = %s\n", i, j, cmd[i].args[j]);
				j++;
			}
			printf("\n");
			i++;
		}
		free_cmd(cmd);
	}
	return (0);
}

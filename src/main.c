/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 23:23:37 by vimercie         ###   ########.fr       */
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

int	main_tester(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].cmd)
	{
		j = 0;
		printf("cmd[%d].cmd = |%s|\n", i, cmd[i].cmd);
		while (cmd[i].args[j])
		{
			printf("cmd[%d].args[%d] = |%s|\n", i, j, cmd[i].args[j]);
			j++;
		}
		printf("cmd[%d].args[%d] = |%s|\n", i, j, cmd[i].args[j]);
		printf("\n");
		printf("cmd[%d].fdIN = |%d|\n", i, cmd[i].fd_in);
		printf("cmd[%d].fdOUT = |%d|\n", i, cmd[i].fd_out);
		i++;
	}
	return (0);
}

void	handle_history(char *a, char *b)
{
	int	size_a;
	int	size_b;

	size_a = ft_strlen(a);
	size_b = ft_strlen(b);
	if (size_a < size_b)
		size_a = size_b;
	if (ft_strncmp(a, b, size_a) != 0)
			add_history(a);
	ft_strlcpy(b, a, ft_strlen(a) + 1);
}

void	assign_fd(t_command *cmd)
{
	int	prev_fd_out;
	int	i;

	prev_fd_out = STDIN_FILENO;
	i = 0;
	while (i < 1) // while (i < cmd->length)
	{
		cmd[i].fd_in = prev_fd_out;
		if (i == 1 - 1) // if (i == cmd->length - 1)
			cmd[i].fd_out = STDOUT_FILENO;
		else
		{
			int	pipefd[2];

			if (pipe(pipefd) < 0)
				return ;
			cmd[i].fd_out = pipefd[1];
			prev_fd_out = pipefd[0];
		}
		i++;
	}
}

int	main(void)
{
	t_command	*cmd;
	char		*buffer;
	char		previous_buffer[1024];
	int		i;

	previous_buffer[0] = 0;
	while (1)
	{
		buffer = readline("GigaBash$ ");
		handle_history(buffer, previous_buffer);
		cmd = parsing(buffer);
		free(buffer);
		if (cmd != NULL)
		{
			i = 0;
		//	main_tester(cmd);
			assign_fd(cmd);
		//	main_tester(cmd);
			while (cmd[i].cmd) {
				exec_cmd(&cmd[i]);
				i++;
			}
			free_cmd(cmd);
		}
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 18:12:59 by vimercie         ###   ########.fr       */
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
		cmd[i].cmd = NULL;
		while (cmd[i].args[j])
		{
			free(cmd[i].args[j]);
			cmd[i].args[j] = NULL;
			j++;
		}
		i++;
	}
	free(cmd);
	cmd = NULL;
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
		printf("cmd[%d].fdIN = |%d|\n", i, cmd[i].fd_in);
		printf("cmd[%d].fdOUT = |%d|\n", i, cmd[i].fd_out);
		printf("\n");
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

void	assign_fd(t_data *data)
{
	int	prev_fd_out;
	int	i;

	prev_fd_out = STDIN_FILENO;
	i = 0;
	while (i < data->n_cmd) // while (i < cmd->length)
	{
		data->cmd[i].fd_in = prev_fd_out;
		if (i == data->n_cmd - 1) // if (i == cmd->length - 1)
			data->cmd[i].fd_out = STDOUT_FILENO;
		else
		{
			int	pipefd[2];

			if (pipe(pipefd) < 0)
				return ;
			data->cmd[i].fd_out = pipefd[1];
			prev_fd_out = pipefd[0];
		}
		i++;
	}
}

int	main(void)
{
	t_data	data;
	char	*buffer;
	char	previous_buffer[1024];
	int		i;

	previous_buffer[0] = 0;
	while (1)
	{
		buffer = readline("GigaBash$ ");
		parsing(&data, buffer);
		main_tester(data.cmd);
		handle_history(buffer, previous_buffer);
		free(buffer);
		if (data.cmd != NULL)
		{
			i = 0;
			assign_fd(&data);
			while (data.cmd[i].cmd)
			{
				exec_cmd(&data.cmd[i]);
				i++;
			}
			free_cmd(data.cmd);
		}
	}
	return (0);
}

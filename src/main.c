/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/08 17:00:08 by vimercie         ###   ########lyon.fr   */
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

	i = 0;
	free(cmd->pathname);
	while (i < cmd->d.n_arg || i < 1)
	{
		free(cmd->argv[i]);
		i++;
	}
	return (0);
}

void	exit_gigabash(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (data->cmd[i].fd_in > 2)
		{
			printf("closed cmd[%d].fd_in (%d)\n", i, data->cmd[i].fd_in);
			close(data->cmd[i].fd_in);
		}
		if (data->cmd[i].fd_out > 2)
		{
			printf("closed cmd[%d].fd_out (%d)\n", i, data->cmd[i].fd_out);
			close(data->cmd[i].fd_out);
		}
		free_cmd(&data->cmd[i]);
		i++;
	}
}

int	main_tester(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->n_cmd)
	{
		j = 0;
		printf("----- cmd n.%d -----\n", i + 1);
		printf("cmd[%d].pathname = |%s|\n", i, data->cmd[i].pathname);
		while (j < data->cmd[i].d.n_arg || j < 1)
		{
			printf("cmd[%d].argv[%d] = |%s|\n", i, j, data->cmd[i].argv[j]);
			j++;
		}
		printf("cmd[%d].fdIN = |%d|\n", i, data->cmd[i].fd_in);
		printf("cmd[%d].fdOUT = |%d|\n", i, data->cmd[i].fd_out);
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

// void	assign_fd(t_data *data)
// {
// 	int	prev_fd_out;
// 	int	i;

// 	prev_fd_out = STDIN_FILENO;
// 	i = 0;
// 	while (i < data->n_cmd) // while (i < cmd->length)
// 	{
// 		data->cmd[i].fd_in = prev_fd_out;
// 		if (i == data->n_cmd - 1) // if (i == cmd->length - 1)
// 			data->cmd[i].fd_out = STDOUT_FILENO;
// 		else
// 		{
// 			int	pipefd[2];

// 			if (pipe(pipefd) < 0)
// 				return ;
// 			data->cmd[i].fd_out = pipefd[1];
// 			prev_fd_out = pipefd[0];
// 		}
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*buffer;
	char	previous_buffer[1024];
	
	(void)ac;
	(void)av;
	previous_buffer[0] = 0;
	data.env = lst_getenv(envp);
	while (1)
	{
		buffer = readline("GigaBash$ ");
		handle_history(buffer, previous_buffer);
		parsing(buffer, &data);
		main_tester(&data);
		// execute(&data.cmd[0], env);
		free(buffer);
		exit_gigabash(&data);
	}
	return (0);
}

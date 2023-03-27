/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/27 15:06:30 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

// int	signal_return = 0;

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}

int	main_tester(t_data *data)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	buffer = NULL;
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
		j = 0;
		while (j < data->cmd[i].d.n_redir)
		{
			printf("cmd[%d].files[%d].file_name = |%s|\n", i, j, data->cmd[i].d.files[j].file_name);
			printf("cmd[%d].files[%d].fd = |%d|\n", i, j, data->cmd[i].d.files[j].fd);
			printf("cmd[%d].files[%d].is_outfile = |%d|\n", i, j, data->cmd[i].d.files[j].is_outfile);
			j++;
		}
		if (data->cmd[i].fd_in > 2)
		{
			printf("infile = ");
			buffer = get_next_line(data->cmd[i].fd_in);
			if (!buffer)
				printf("(null)");
			else
			{
				printf("\n");
				while (buffer)
				{
					printf("%s", buffer);
					free(buffer);
					buffer = get_next_line(data->cmd[i].fd_in);
				}
			}
		}
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

int	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (data->cmd[i].d.pipefd[0] > 2
			|| data->cmd[i].d.pipefd[1] > 2)
		{
			close(data->cmd[i].d.pipefd[0]);
			close(data->cmd[i].d.pipefd[1]);
			printf("closed pipe[0] = %d\n", data->cmd[i].d.pipefd[0]);
			printf("closed pipe[1] = %d\n", data->cmd[i].d.pipefd[1]);
			return (0);
		}
		i++;
	}
	return (0);
}

void	free_memory(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data)
	{
		close_pipes(data);
		while (i < data->n_cmd)
		{
			j = 0;
			free_tab(data->cmd[i].argv);
			while (j < data->cmd[i].d.n_redir)
			{
				if (data->cmd[i].d.files[j].fd > 2)
				{
					close(data->cmd[i].d.files[j].fd);
					printf("closed fd = %d\n", data->cmd[i].d.files[j].fd);
				}
				free(data->cmd[i].d.files[j].file_name);
				j++;
			}
			free(data->cmd[i].d.files);
			free(data->cmd[i].pathname);
			i++;
		}
		free(data->cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*buffer;
	char	previous_buffer[1024];
	struct sigaction sa;
	
	(void)ac;
	(void)av;
	previous_buffer[0] = 0;
	data.env = lst_getenv(envp);
	data.tab_env = lst_env_to_tab_env(data.env);
	while (1)
	{
		buffer = readline("GigaBash$ ");
		signal_handling(sa, buffer);
		handle_history(buffer, previous_buffer);
		parsing(buffer, &data);
		main_tester(&data);
		// execute(&data, buffer);
		envp = lst_env_to_tab_env(data.env);
		free(buffer);
		free_memory(&data);
	}
	return (0);
}

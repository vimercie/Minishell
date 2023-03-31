/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/31 18:20:31 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

// int	signal_return = 0;

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
	struct sigaction sa;
	
	(void)ac;
	(void)av;
	previous_buffer[0] = 0;
	data.env = lst_getenv(envp);
	while (1)
	{
		data.tab_env = lst_env_to_tab_env(data.env);
		signal_handling(sa, &data);
		buffer = readline("GigaBash$ ");
		if (buffer == NULL)
		{
			printf("EXIT_BASH\n\n");
			free_tab(data.tab_env);
			exit(EXIT_SUCCESS);
		}
		handle_history(buffer, previous_buffer);
		parsing(buffer, &data);
		// main_tester(&data);
		execute(&data, buffer);
		main_tester(&data);
		// execute(&data, buffer);
		data.tab_env = lst_env_to_tab_env(data.env);
		free(buffer);
		free_memory(&data);
	}
	return (0);
}

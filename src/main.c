/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 15:00:05 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_err_no;

void	handle_history(char *buffer, char *previous_buffer)
{
	int	size_buffer;
	int	size_previous_buffer;

	size_buffer = ft_strlen(buffer);
	size_previous_buffer = ft_strlen(previous_buffer);
	if (size_buffer < size_previous_buffer)
		size_buffer = size_previous_buffer;
	if (ft_strncmp(buffer, previous_buffer, size_buffer) != 0)
		add_history(buffer);
	ft_strlcpy(previous_buffer, buffer, ft_strlen(buffer) + 1);
}

int	main(int ac, char **av, char **envp)
{
	t_data				data;
	char				*buffer;
	char				previous_buffer[1024];

	(void)ac;
	(void)av;
	previous_buffer[0] = 0;
	data.env = lst_getenv(envp);
	data.tab_env = lst_env_to_tab_env(data.env);
	while (1)
	{
		signal_handling(&data.sa);
		buffer = readline("GigaBash$ ");
		if (!buffer)
			break ;
		handle_history(buffer, previous_buffer);
		if (parsing(buffer, &data))
			execute_commands(&data, buffer);
		free(buffer);
		free_loop(&data);
	}
	printf("exit\n");
	free_tab(data.tab_env);
	lst_free(data.env);
	return (0);
}

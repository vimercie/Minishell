/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/08 04:28:27 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
		signal_handling(sa);
		buffer = readline("GigaBash$ ");
		if (buffer == NULL)
		{
			printf("EXIT_BASH\n\n");
			free_tab(data.tab_env);
			lst_free(data.env);
			exit(EXIT_SUCCESS);
		}
		handle_history(buffer, previous_buffer);
		parsing(buffer, &data);
		main_tester(&data);
		execute_commands(&data);
		data.tab_env = lst_env_to_tab_env(data.env);
		free(buffer);
		free_memory(&data);
	}
	return (0);
}

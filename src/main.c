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
	printf("buffer 1=%s\nbuffer 2=%s\n", a, b);
	printf("strcomp return = %d\n", ft_strncmp(a, b, size_a));
	if (ft_strncmp(a, b, size_a) != 0)
			add_history(a);
	ft_strlcpy(b, a, ft_strlen(a) + 1);
}

int	main(void)
{
	t_command	*cmd;
	char		*buffer;
	char		previous_buffer[1024];

	previous_buffer[0] = 0;
	while (1)
	{
		buffer = readline("GigaBash$ ");
		handle_history(buffer, previous_buffer);
		cmd = parsing(buffer);
		free(buffer);
		if (cmd)
		{
<<<<<<< HEAD
			//main_tester(cmd);
			exec_cmd(cmd);
=======
			main_tester(cmd);
			// exec_cmd(cmd);
>>>>>>> 2a63f611779001a7be51e5f69e4e4d68a470f618
			free_cmd(cmd);
		}
	}
	return (0);
}

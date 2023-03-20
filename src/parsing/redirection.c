/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/20 23:42:35 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_pipe(int fd_to_close, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (fd_to_close > 2
			&& (fd_to_close == data->cmd[i].d.pipefd[0]
			|| fd_to_close == data->cmd[i].d.pipefd[1]))
		{
			close(data->cmd[i].d.pipefd[0]);
			close(data->cmd[i].d.pipefd[1]);
			printf("closed pipe :\nfd[0] = %d\nfd[1] = %d\n", data->cmd[i].d.pipefd[0], data->cmd[i].d.pipefd[1]);
			return (0);
		}
		i++;
	}
	return (0);
}

int get_fd(char *operator, char *file_name)
{
	int		fd;

	fd = -1;
	if (!file_name)
		return (fd);
	if (access(file_name, W_OK) == 0 || access(file_name, F_OK) == -1)
	{
		if (ft_strcmp(operator, ">") == 0)
			fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (ft_strcmp(operator, ">>") == 0)
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (ft_strcmp(operator, "<") == 0)
			fd = open(file_name, O_RDONLY);
	}
	return (fd);
}

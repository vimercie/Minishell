/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/21 23:27:02 by vimercie         ###   ########lyon.fr   */
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

int get_fd(char *operator, char *file_name, t_data *data)
{
	int		fd;

	fd = -1;
	if (!file_name)
		return (fd);
	if (operator[0] == '>')
	{
		if (access(file_name, W_OK) == 0 || access(file_name, F_OK) == -1)
		{
			if (ft_strcmp(operator, ">") == 0)
				fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			else if (ft_strcmp(operator, ">>") == 0)
				fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
	}
	else if (ft_strcmp(operator, "<") == 0)
	{
		if (access(file_name, R_OK) == 0)
			fd = open(file_name, O_RDONLY);
	}
	else if (ft_strcmp(operator, "<<") == 0)
		fd = heredoc(file_name, data);
	return (fd);
}

t_file_table	*files_init(char **tokens, int n_redir, t_data *data)
{
	t_file_table	*files;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!tokens || n_redir == 0)
		return (NULL);
	files = ft_calloc(n_redir + 1, sizeof(t_file_table));
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			files[j].file_name = ft_strdup(tokens[i + 1]);
			files[j].fd = get_fd(tokens[i], tokens[i + 1], data);
			files[j].is_outfile = 0;
			files[j].is_heredoc = 0;
			if (tokens[i][0] == '>')
				files[j].is_outfile = 1;
			if (ft_strcmp(tokens[i], "<<") == 0)
				files[j].is_heredoc = 1;
			j++;
		}
		i++;
	}
	return (files);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:04:19 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/21 02:42:12 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_duplicate(int file_index, t_file_table *files)
{
	int	i;

	i = 0;
	if (file_index <= 0
		|| files[i].is_heredoc != files[file_index].is_heredoc
		|| files[i].is_outfile != files[file_index].is_outfile)
		return (-1);
	while (i < file_index)
	{
		if (ft_strcmp(files[file_index].file_name, files[i].file_name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	get_fd(char *operator, char *file_name, t_data *data)
{
	int		fd;

	if (!file_name)
		return (-1);
	if (operator[0] == '>')
	{
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) == -1)
			return (-1);
		if (ft_strcmp(operator, ">") == 0)
			fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else if (ft_strcmp(operator, ">>") == 0)
			fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	else if (ft_strcmp(operator, "<") == 0)
	{
		if (access(file_name, R_OK) == -1)
			return (-1);
		fd = open(file_name, O_RDONLY);
	}
	else if (ft_strcmp(operator, "<<") == 0)
		fd = heredoc(file_name, data);
	return (fd);
}

int	set_files(char **tokens, t_file_table *file)
{
	if (tokens[0][0] == '>')
	{
		file->is_outfile = 1;
		if (ft_strcmp(tokens[0], ">>") == 0)
			file->is_outfile = 2;
	}
	if (ft_strcmp(tokens[0], "<<") == 0)
		file->is_heredoc = 1;
	file->file_name = ft_strdup(tokens[1]);
	return (1);
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
			if (!tokens[i + 1])
				return (files);
			set_files(tokens + i, &files[j]);
			if (find_duplicate(j, files) == -1)
				files[j].fd = get_fd(tokens[i], tokens[i + 1], data);
			else
				files[j].fd = files[find_duplicate(j, files)].fd;
			j++;
		}
		i++;
	}
	return (files);
}

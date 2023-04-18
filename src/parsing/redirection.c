/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:04:19 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/17 20:16:52 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

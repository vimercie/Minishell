/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/23 15:03:32 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// compte le nombre de redirections

int	redirect_count(char *input, char c)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			res++;
			while (input[i] == c)
				i++;
		}
		i++;
	}
	return (res);
}

// renvoie le fd du fichier suivant l'operateur de redirection

int get_fd(char *input)
{
	char	*file_name;
	int		start;
	int		fd;
	int 	i;

	i = 0;
	fd = -1;
	while (input[i] == input[0])
		i++;
	while (ft_isspace(input[i]) && input[i])
		i++;
	start = i;
	while (!ft_isspace(input[i]) && input[i])
		i++;
	file_name = ft_substr(input, start, i - start);
	if (access(file_name, W_OK) == 0 || access(file_name, F_OK) == -1)
	{
		if (input[1] == input[0])
			fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
		fd = open(file_name, O_CREAT | O_RDWR, 0666);
	}
	free(file_name);
	return (fd);
}

int redirect_fd(char *input, t_command *cmd)
{
	int i;

	i = 0;
	while (input[0])
	{
		if (input[0] == '>')
		{
			cmd->fd_out = get_fd(input);
			while (input[0] == '>' && input[0])
				input++;
			while (ft_isspace(input[0]) && input[0])
				input++;
			while (!ft_isspace(input[0]) && input[0])
				input++;
		}
		else if (input[0] == '<')
		{
			cmd->fd_in = get_fd(input);
			while (input[0] == '<' && input[0])
				input++;
			while (ft_isspace(input[0]) && input[0])
				input++;
			while (!ft_isspace(input[0]) && input[0])
				input++;
		}
		else
			input++;
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/20 15:15:50 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int redirect_output(char *input)
{
	char	*file_name;
	int		start;
	int 	i;

	i = 0;
	while (input[i] == input[0] && input[i])
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
			return (open(file_name, O_CREAT, O_RDWR, O_APPEND));
		return (open(file_name, O_CREAT, O_RDWR));
	}
	return (-1);
}

int redirect_fd(char *input, t_command *cmd)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
				cmd->fd_out = redirect_output(input + i);
		i++;
	}
	return (1);
}
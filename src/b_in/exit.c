/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:15:28 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/10 02:55:52 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int signal_return;

int	exit_bash(t_data *data, char *buffer)
{
	if ((ft_strncmp(buffer, "exit ", 4)  == 0) || signal_return != 0)
	{
		exit_gigabash(data);
		lst_free(data->env);
		free(buffer);
		return (1);
	}
	return (0);
}
void signal_exit(int signum)
{	
	if (signum  == SIGINT)
		signal_return = 1;
	return ;
}

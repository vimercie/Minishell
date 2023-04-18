/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:18:52 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/18 13:22:32 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	built_in_detection(t_data *data, t_command *cmd, char *buffer)
{
	int	return_val;

	return_val = -1;
	if (buffer[0] == '\0')
		return (0);
	else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return_val = echo_controller(cmd);
	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return_val = cd(data);
	else if ((ft_strncmp(cmd->argv[0], "export", 6) == 0) && cmd->d.n_arg == 1)
	{
		return_val = 0;
		print_sorted_list(data->env);
	}
	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0 && cmd->d.n_arg >= 2)
		return_val = export_controller(cmd, data->env);
	else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		return_val = print_list(data->env);
	else if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return_val = get_current_dir();
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return_val = unset_var(cmd, data->env);
	else if (ft_strncmp(buffer, "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	return (return_val);
}

int	dup_fd(t_command *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2 stdin");
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2 stdout");
		close(cmd->fd_out);
	}
	return (1);
}

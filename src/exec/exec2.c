/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:18:52 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/20 14:37:54 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	close_pipes(t_command *cmd, t_data *data)
{
	int	return_val;

	return_val = 1;
	if (is_pipe(cmd->fd_in, data) && cmd->fd_in != STDIN_FILENO)
		return_val = close(cmd->fd_in);
	if (is_pipe(cmd->fd_out, data) && cmd->fd_out != STDOUT_FILENO)
		return_val = close(cmd->fd_out);
	return (return_val);
}

int	dup_fd(t_command *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2 stdin");
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2 stdout");
	}
	return (1);
}

int	built_in_detection(t_command *cmd, t_data *data)
{
	int	return_val;

	return_val = -1;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return_val = echo_controller(cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return_val = cd(data);
	else if ((ft_strcmp(cmd->argv[0], "export") == 0) && cmd->d.n_arg == 1)
	{
		return_val = 0;
		print_sorted_list(data->env);
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg >= 2)
		return_val = export_controller(cmd, data->env);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return_val = print_list(data->env);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return_val = get_current_dir();
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return_val = unset_var(cmd, data->env);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	return (return_val);
}

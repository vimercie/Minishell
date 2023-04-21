/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:18:52 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/21 08:24:32 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (data->cmd[i].d.pipefd[0] > 2)
		{
			if (close(data->cmd[i].d.pipefd[0]) == -1)
				exit(print_linux_error("close"));
		}
		if (data->cmd[i].d.pipefd[1] > 2)
		{
			if (close(data->cmd[i].d.pipefd[1]) == -1)
				exit(print_linux_error("close"));
		}
		i++;
	}
	return (1);
}

int	dup_fd(t_command *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2");
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2");
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
	else if (ft_strcmp(cmd->argv[0], "exit") == 0 && cmd->d.n_arg == 2)
		exit_bash(data, NULL, ft_atoi(cmd->argv[1]));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0 && cmd->d.n_arg == 1)
		exit_bash(data, NULL, EXIT_SUCCESS);
	return (return_val);
}

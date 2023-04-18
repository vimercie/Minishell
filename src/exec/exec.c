/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/18 11:32:22 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_single_b_in(t_command *cmd, char *buffer, t_data *data)
{
	int	tmp_stdin;
	int	tmp_stdout;

	if (cmd->fd_in != STDIN_FILENO)
		tmp_stdin = dup(STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		tmp_stdout = dup(STDOUT_FILENO);
	dup_fd(cmd);
	built_in_detection(data, cmd, buffer);
	if (cmd->fd_in != STDIN_FILENO)
		dup2(tmp_stdin, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(tmp_stdout, STDOUT_FILENO);
	return (1);
}

int	child_p(t_data *data, int i, char *buffer)
{
	dup_fd(&data->cmd[i]);
	if (data->cmd[i].d.is_builtin == 1)
		exit(built_in_detection(data, &data->cmd[i], buffer));
	data->tab_env = lst_env_to_tab_env(data->env);
	execve(data->cmd[i].pathname, data->cmd[i].argv, data->tab_env);
	perror_exit("execve");
	return (0);
}

void	cmd_loop(t_data *data, char *buffer)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		data->cmd[i].d.pid = fork();
		if (data->cmd[i].d.pid == -1)
			perror_exit("fork");
		else if (data->cmd[i].d.pid == 0)
			child_p(data, i, buffer);
		if (data->cmd[i].fd_in != STDIN_FILENO)
			close(data->cmd[i].fd_in);
		if (data->cmd[i].fd_out != STDOUT_FILENO)
			close(data->cmd[i].fd_out);
		i++;
	}
}

int	execute_commands(t_data *data, char *buffer)
{
	int	status;
	int	i;

	if (data->cmd[0].d.is_builtin && data->n_cmd == 1)
		return (exec_single_b_in(&data->cmd[0], buffer, data));
	cmd_loop(data, buffer);
	i = 0;
	while (i < data->n_cmd)
	{
		if (waitpid(data->cmd[i].d.pid, &status, 0) == -1)
			return (print_bash_error("waitpid", 1));
		if (WIFEXITED(status))
			g_err_no = WEXITSTATUS(status);
		// if (WIFSIGNALED(status))
		i++;
	}
	return (1);
}

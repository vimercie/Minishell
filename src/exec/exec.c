/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/20 23:31:45 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_single_b_in(t_command *cmd, t_data *data)
{
	int	tmp_stdin;
	int	tmp_stdout;

	if (cmd->fd_in != STDIN_FILENO)
		tmp_stdin = dup(STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		tmp_stdout = dup(STDOUT_FILENO);
	dup_fd(cmd);
	g_err_no = built_in_detection(cmd, data);
	if (cmd->fd_in != STDIN_FILENO)
		dup2(tmp_stdin, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(tmp_stdout, STDOUT_FILENO);
	return (1);
}

int	wait_child_processes(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (waitpid(data->cmd[i].d.pid, &status, WUNTRACED) == -1)
			return (print_bash_error("waitpid", 1));
		if (WIFEXITED(status))
			g_err_no = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			printf("\n");
		i++;
	}
	return (1);
}

int	child_p(t_command *cmd, t_data *data)
{
	signal_handling(&data->sa);
	dup_fd(cmd);
	close_pipes(data);
	if (cmd->d.is_builtin == 1)
		exit(built_in_detection(cmd, data));
	data->tab_env = lst_env_to_tab_env(data->env);
	execve(cmd->pathname, cmd->argv, data->tab_env);
	return (0);
}

int	cmd_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		signal_ignore(data);
		data->cmd[i].d.pid = fork();
		if (data->cmd[i].d.pid == -1)
			return (print_linux_error("fork"));
		else if (data->cmd[i].d.pid == 0)
			child_p(&data->cmd[i], data);
		i++;
	}
	return (1);
}

int	execute_commands(t_data *data)
{
	if (data->cmd[0].d.is_builtin && data->n_cmd == 1)
		return (exec_single_b_in(&data->cmd[0], data));
	cmd_loop(data);
	close_pipes(data);
	wait_child_processes(data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/21 02:12:57 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_single_b_in(t_command *cmd, t_data *data)
{
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	if (tmp_stdin == -1 || tmp_stdout == -1)
		return (print_linux_error("dup"));
	dup_fd(cmd);
	g_err_no = built_in_detection(cmd, data);
	if (dup2(tmp_stdin, STDIN_FILENO) == -1
		|| dup2(tmp_stdout, STDOUT_FILENO) == -1)
		return (print_linux_error("dup2"));
	if (close(tmp_stdin) == -1
		|| close(tmp_stdout) == -1)
		return (print_linux_error("close"));
	return (1);
}

int	wait_child_process(int pid)
{
	int	status;

	if (waitpid(pid, &status, WUNTRACED) == -1)
		exit(print_linux_error("waitpid"));
	if (WIFEXITED(status))
		g_err_no = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_err_no = 130;
		if (WTERMSIG(status) == SIGQUIT)
			g_err_no = 131;
	}
	return (1);
}

int	child_p(t_command *cmd, t_data *data)
{
	dup_fd(cmd);
	close_pipes(data);
	if (cmd->d.is_builtin == 1)
		exit(built_in_detection(cmd, data));
	child_signal_handling(&data->sa);
	data->tab_env = lst_env_to_tab_env(data->env);
	execve(cmd->pathname, cmd->argv, data->tab_env);
	return (0);
}

int	exec_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
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
	int	i;

	i = 0;
	exec_signal_handling(&data->sa);
	if (data->cmd[0].d.is_builtin && data->n_cmd == 1)
		return (exec_single_b_in(&data->cmd[0], data));
	exec_loop(data);
	close_pipes(data);
	while (i < data->n_cmd)
	{
		wait_child_process(data->cmd[i].d.pid);
		i++;
	}
	if (g_err_no == 130)
		ft_putchar_fd('\n', 2);
	if (g_err_no == 131)
		ft_putstr_fd("Quit\n", 2);
	return (1);
}

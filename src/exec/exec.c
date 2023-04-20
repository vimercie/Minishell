/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/20 15:07:32 by mmajani          ###   ########lyon.fr   */
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
	g_err_no = built_in_detection(data, cmd, buffer);
	if (cmd->fd_in != STDIN_FILENO)
		dup2(tmp_stdin, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(tmp_stdout, STDOUT_FILENO);
	return (1);
}

void	child_p(t_data *data, int i, char *buffer)
{
	signal_handling(&data->sa);
	dup_fd(&data->cmd[i]);
	if (data->cmd[i].d.is_builtin == 1)
		exit(built_in_detection(data, &data->cmd[i], buffer));
	data->tab_env = lst_env_to_tab_env(data->env);
	execve(data->cmd[i].pathname, data->cmd[i].argv, data->tab_env);
	perror_exit("execve");
}

void	cmd_loop(t_data *data, char *buffer)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		data->sa.sa_handler = SIG_IGN;
		sigemptyset(&data->sa.sa_mask);
		data->sa.sa_flags = 0;
		if (sigaction(SIGINT, &data->sa, NULL) == -1)
			perror("sigaction");
		data->cmd[i].d.pid = fork();
		if (data->cmd[i].d.pid == -1)
			perror_exit("fork");
		else if (data->cmd[i].d.pid == 0)
			child_p(data, i, buffer);
		if (is_pipe(data->cmd[i].fd_in, data)
			&& data->cmd[i].fd_in != STDIN_FILENO)
		{
			printf("closing fd_in = %d\n", data->cmd[i].fd_in);
			close(data->cmd[i].fd_in);
		}
		if (is_pipe(data->cmd[i].fd_out, data)
			&& data->cmd[i].fd_out != STDOUT_FILENO)
		{
			printf("closing fd_out = %d\n", data->cmd[i].fd_out);
			close(data->cmd[i].fd_out);
		}
		i++;
	}
	return ;
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
		if (WIFSIGNALED(status))
			printf("\n");
		i++;
	}
	return (1);
}

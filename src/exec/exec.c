/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/03 18:27:04 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define STDIN 0
#define STDOUT 1

int	built_in_detection(t_data *data, char *buffer)
{
	if (buffer[0] == '\0')
		return (0);
	else if (ft_strncmp(data->cmd->argv[0], "echo", 4) == 0)
		return (echo_controller(data->cmd));
	else if (ft_strncmp(data->cmd->argv[0], "cd", 2) == 0)
		return (cd(data));
	else if (ft_strncmp(data->cmd->argv[0], "export", 6) == 0 && data->cmd->d.n_arg == 1)
		return (print_sorted_list(data->env));
	else if (ft_strncmp(data->cmd->argv[0], "export", 6) == 0 && data->cmd->d.n_arg >= 2)
		return (export_controller(data->cmd, data->env));
	else if (ft_strncmp(data->cmd->argv[0], "pwd", 3) == 0)
		return (get_current_dir());
	else if (ft_strncmp(data->cmd->argv[0], "unset", 5) == 0)
		return (unset_var(data->cmd, data->env));
	else if (ft_strncmp(buffer, "exit", 4) == 0)
		exit((exit_bash(data, buffer)));
	return (-1);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	close_exec_exit(t_data *data, int i)
{
	close(data->cmd[i].d.pipefd[0]);
	close(data->cmd[i].d.pipefd[1]);
	execve(data->cmd[i].pathname, data->cmd[i].argv, data->tab_env);
	perror_exit("execve");
}

void child_p(t_data *data, int i)
{
    if (data->cmd[i].fd_in != STDIN_FILENO)
        if (dup2(data->cmd[i].fd_in, STDIN_FILENO) == -1)
            perror_exit("dup2");
    if (data->cmd[i].fd_out != STDOUT_FILENO)
        if (dup2(data->cmd[i].fd_out, STDOUT_FILENO) == -1)
            perror_exit("dup2");
    close_exec_exit(data, i);
}

void	execute_commands(t_data *data)
{
	pid_t pid;
	int i;

	i = 0;
	while (i < data->n_cmd)
	{
		pid = fork();
		if (pid == -1)
			perror_exit("fork");
		else if (pid == 0)
			child_p(data, i);
		else
		{ // parent process
			close(data->cmd[i].fd_in);
			close(data->cmd[i].fd_out);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}

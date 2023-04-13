/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/13 14:11:20 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define STDIN 0
#define STDOUT 1

int	built_in_detection(t_data *data, t_command *cmd, char *buffer, t_env *env)
{
	if (buffer[0] == '\0')
		return (0);
	else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (echo_controller(cmd));
	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (cd(data));
	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0
		&& cmd->d.n_arg == 1)
		return (print_sorted_list(env));
	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0
		&& cmd->d.n_arg >= 2)
		return (export_controller(cmd, env));
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (print_list(data->env));
	else if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (get_current_dir());
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (unset_var(cmd, env));
	else if (ft_strncmp(buffer, "exit", 4) == 0)
		exit((exit_bash(data, buffer)));
	return (-1);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	child_p(t_data *data, int i, char *buffer)
{
	if (data->cmd[i].fd_in != STDIN_FILENO)
	{
		if (dup2(data->cmd[i].fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2 stdin");
		close(data->cmd[i].fd_in);
	}
	if (data->cmd[i].fd_out != STDOUT_FILENO)
	{
		if (dup2(data->cmd[i].fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2 stdout");
		close(data->cmd[i].fd_out);
	}
	if (built_in_detection(data, &data->cmd[i], buffer, data->env) == -1)
	{
		execve(data->cmd[i].pathname, data->cmd[i].argv, data->tab_env);
		perror_exit("execve");
	}
	else
		exit(0);
	return ;
}

void	execute_commands(t_data *data, char *buffer)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->n_cmd)
	{
		if (!data->cmd[i].pathname)
			return ;
		pid = fork();
		if (pid == -1)
			perror_exit("fork");
		else if (pid == 0)
			child_p(data, i, buffer);
		else
		{
			if (data->cmd[i].fd_in != STDIN_FILENO)
				close(data->cmd[i].fd_in);
			if (data->cmd[i].fd_out != STDOUT_FILENO)
				close(data->cmd[i].fd_out);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:08:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/16 04:41:00 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define STDIN 0
#define STDOUT 1

// int	built_in_detection(t_data *data, t_command *cmd, char *buffer)
// {
// 	if (buffer[0] == '\0')
// 		return (0);
// 	else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
// 		return (echo_controller(cmd));
// 	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
// 		return (cd(data));
// 	else if ((ft_strncmp(cmd->argv[0], "export", 6) == 0) && cmd->d.n_arg == 1)
// 		return (print_sorted_list(data->env));
// 	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0 && cmd->d.n_arg >= 2)
// 		return (export_controller(cmd, data->env));
// 	else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
// 		return (print_list(data->env));
// 	else if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
// 		return (get_current_dir());
// 	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
// 		return (unset_var(cmd, data->env));
// 	else if (ft_strncmp(buffer, "exit", 4) == 0)
// 		exit((exit_bash(data, buffer)));
// 	return (-1);
// }

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
		return_val = print_sorted_list(data->env);
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
	exit(return_val);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	child_p(t_data *data, int i, char *buffer)
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
	if (data->cmd->d.is_builtin)
		built_in_detection(data, &data->cmd[i], buffer);
	data->tab_env = lst_env_to_tab_env(data->env);
	execve(data->cmd[i].pathname, data->cmd[i].argv, data->tab_env);
	perror_exit("execve");
	return (0);
}

int	execute_commands(t_data *data, char *buffer)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		data->cmd->d.pid = fork();
		if (data->cmd->d.pid == -1)
			perror_exit("fork");
		else if (data->cmd->d.pid == 0)
			child_p(data, i, buffer);
		if (data->cmd[i].fd_in != STDIN_FILENO)
			close(data->cmd[i].fd_in);
		if (data->cmd[i].fd_out != STDOUT_FILENO)
			close(data->cmd[i].fd_out);
		i++;
	}
	i = 0;
	while (i < data->n_cmd)
	{
		waitpid(0, NULL, 0);
		i++;
	}
	return (1);
}

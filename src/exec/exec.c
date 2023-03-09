#include "../../inc/minishell.h"

int	built_in_detection(t_data *data)
{
	if (ft_strcmp(data->cmd->argv[0], "echo") == 0)
		return (echo_n(data->cmd));
	else if (ft_strcmp(data->cmd->argv[0], "export") == 0 && data->cmd->d.n_arg == 1)
		return (print_list(data->env));
	else if (ft_strcmp(data->cmd->argv[0], "export") == 0 && data->cmd->d.n_arg >= 2)
		return (export_controller(data->cmd, data->env));
	else if (ft_strcmp(data->cmd->argv[0], "pwd") == 0)
		return (get_current_dir());
	else if (ft_strcmp(data->cmd->argv[0], "pwd"))
		return (unset_var(data->cmd, data->env));
	else if (ft_strcmp(data->cmd->argv[0], "exit"))
		return (exit_bash(data));
	return (-1);
}

int	execute(t_data *data)
{
	built_in_detection(data);
	return (0);
}

#include "../../inc/minishell.h"

int	built_in_detection(t_data *data, char *buffer)
{
	if (ft_strncmp(data->cmd->argv[0], "echo", 4) == 0)
		return (echo_n(data->cmd));
	else if (ft_strncmp(data->cmd->argv[0], "export", 6) == 0 && data->cmd->d.n_arg == 1)
		return (print_list(data->env));
	else if (ft_strncmp(data->cmd->argv[0], "export", 6) == 0 && data->cmd->d.n_arg >= 2)
		return (export_controller(data->cmd, data->env));
	else if (ft_strncmp(data->cmd->argv[0], "pwd", 3) == 0)
		return (get_current_dir());
	else if (ft_strncmp(data->cmd->argv[0], "unset", 5 == 0))
		return (unset_var(data->cmd, data->env));
	else if (ft_strncmp(buffer, "exit", 4) == 0)
		exit((exit_bash(data, buffer)));
	return (-1);
}

int	execute(t_data *data, char *buffer)
{
	built_in_detection(data, buffer);
	printf("out of execute\n");
	return (0);
}

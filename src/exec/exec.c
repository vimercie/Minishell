#include "../../inc/minishell.h"

int     built_in_detection(t_command *cmd, t_env *env)
{
	(void)env;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (echo_n(cmd));
	else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg == 1)
		return (print_list(env));
	else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg >= 2)
		return (export_controller(cmd, env));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (get_current_dir());
	else if (ft_strcmp(cmd->argv[0], "pwd"))
		return (unset_var(cmd, env));
	return (-1);
}

int     execute(t_command *cmd, t_env *env)
{
	built_in_detection(cmd, env);
	return (0);
}

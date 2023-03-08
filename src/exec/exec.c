#include "../../inc/minishell.h"

int     built_in_detection(t_command *cmd, t_env *env)
{
	(void)env;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		printf("using BUILT_IN\n");
		return (echo_n(cmd));
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg == 1)
	{
		return (print_list(env));
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg == 2)
		return (export(cmd->argv[1], env));
	return (-1);
}

int     execute(t_command *cmd, t_env *env)
{
	built_in_detection(cmd, env);
	return (0);
}

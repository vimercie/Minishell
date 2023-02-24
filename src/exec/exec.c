#include "../../inc/minishell.h"

int     built_in_detection(t_command *cmd, char **envp)
{
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
    {
        printf("using BUILT_IN\n");
        return (echo_n(cmd));
    }
    else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg == 1)
        return (print_ascii_order_env(envp));
    else if (ft_strcmp(cmd->argv[0], "export") == 0 && cmd->d.n_arg == 2)
        return (export(cmd->argv[1], envp));
    return (-1);
}

int     execute(t_command *cmd, char **envp)
{
    built_in_detection(cmd, envp);
    return (0);
}

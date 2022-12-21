#include "../../inc/minishell.h"

int echo_n(t_command *cmd)
{
    int n;

    if (cmd->args[1] == NULL)
    {
        printf("\n");
        return (1);
    }
    else if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
        n = 1;
    else if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 1)
        n = 0;
    if (n == 1)
    {
        if (cmd->args[2] == NULL)
            return (1);
        printf("%s", cmd->args[2]);
    }
    else
        printf("%s\n", cmd->args[1]);
    return (1);
}

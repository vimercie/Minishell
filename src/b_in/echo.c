#include "../../inc/minishell.h"

int echo_n(t_command *cmd)
{
    int n;

    if (cmd->argv[1] == NULL)
    {
        printf("\n");
        return (1);
    }
    else if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0)
        n = 1;
    else if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 1)
        n = 0;
    if (n == 1)
    {
        if (cmd->argv[2] == NULL)
            return (1);
        printf("%s", cmd->argv[2]);
    }
    else
        printf("%s\n", cmd->argv[1]);
    return (1);
}

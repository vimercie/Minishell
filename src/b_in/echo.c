#include "../../inc/minishell.h"

int echo(char *str)
{
	printf("%s", str);
	return (0);
}

int has_n_option(t_command *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[i] && ft_strcmp(cmd->argv[1], "-n") != 0)
		return (0);
	while (cmd->argv[i] && (ft_strcmp(cmd->argv[i], "-n") == 0))
		i++;
	return (i);
}

int echo_controller(t_command *cmd)
{
	int i;
	int n_option;

	i = 1;
	if (!cmd->argv[1])
		return (printf("\n"));
	n_option = has_n_option(cmd);
	if (n_option > 0)
		i = n_option;
	while (cmd->argv[i] && i < cmd->d.n_arg)
	{
		echo(cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (n_option == 0)
		printf("\n");
	return (0);
}
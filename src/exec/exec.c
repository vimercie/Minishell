#include "../../inc/minishell.h"

int		exec_cmd(t_command *cmd)
{
	pid_t	pid;

    pid = fork();
	if (pid == 0)
	{
		if (cmd->fd_in != STDIN_FILENO)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		if (cmd->has_pipe)
			execve(cmd->cmd, cmd->args, NULL);
		else
			execve(cmd->cmd, cmd->args, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
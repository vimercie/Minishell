#include "../../inc/minishell.h"

int     built_in_detection(t_command *cmd)
{
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        return (echo_n(cmd));
    return (0);
}

int exec_cmd(t_command *cmd)
{
	pid_t	pid;
	int		status;

    if (built_in_detection(cmd) == 1)
	{}
        return (EXIT_SUCCESS);
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
	waitpid(pid, &status, 0);
	rl_on_new_line();
	return (EXIT_SUCCESS);
}
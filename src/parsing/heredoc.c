/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:28:45 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/19 14:00:51 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	heredoc_putfd(char *buffer, int heredoc_fd, t_env *env)
{
	char	*res;

	res = handle_env_var(buffer, true, env);
	ft_putstr_fd(res, heredoc_fd);
	ft_putstr_fd("\n", heredoc_fd);
	free(res);
	return (1);
}

int	heredoc_loop(char *delimiter, int heredoc_fd, t_env *env)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (!buffer || ft_strcmp(buffer, delimiter) == 0)
			break ;
		heredoc_putfd(buffer, heredoc_fd, env);
		free(buffer);
	}
	if (!buffer)
		print_heredoc_warning(delimiter);
	free(buffer);
	return (1);
}

int	heredoc(char *delimiter, t_data *data)
{
	char	*res;
	int		pipefd[2];
	int		pid;
	int		status;

	res = NULL;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		heredoc_loop(delimiter, pipefd[1], data->env);
		exit(1);
	}
	else if (waitpid(-1, &status, 0) == -1)
		return (-1);
	close(pipefd[1]);
	free(res);
	return (pipefd[0]);
}

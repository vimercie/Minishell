/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:28:45 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/18 11:04:43 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_subft(t_data *data, char *buffer, char *tmp, char *res)
{
	tmp = handle_env_var(buffer, data->env);
	free(buffer);
	buffer = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	if (res)
		tmp = ft_strjoin(res, "\n");
	free(res);
	res = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
}

char	*heredoc_loop(char *delimiter, t_data *data)
{
	char	*buffer;
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || ft_strcmp(buffer, delimiter) == 0)
			break ;
		heredoc_subft(data, buffer, tmp, res);
	}
	if (!buffer)
		print_heredoc_warning(delimiter);
	free(buffer);
	return (res);
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
		res = heredoc_loop(delimiter, data);
		ft_putstr_fd(res, pipefd[1]);
		exit(1);
	}
	else if (waitpid(-1, &status, 0) == -1)
		return (-1);
	close(pipefd[1]);
	free(res);
	return (pipefd[0]);
}

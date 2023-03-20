/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:28:45 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/16 16:17:05 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*heredoc_loop(char *delimiter)
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
		if (buffer[0] && !ft_strcmp(buffer, delimiter))
			break ;
		if (res)
			tmp = ft_strjoin(res, "\n");
		free(res);
		res = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	free(buffer);
	return (res);
}

int	heredoc(char *delimiter)
{
	char	*hd;

	hd = heredoc_loop(delimiter);
	printf("%s\n", hd);
	free(hd);
	return (0);
}
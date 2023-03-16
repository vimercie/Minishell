/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:28:45 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/16 15:49:57 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_loop(char *eof)
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
		if (!ft_strcmp(buffer, eof))
			break ;
		if (res)
			tmp = ft_strjoin(res, "\n");
		free(res);
		res = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	printf("\nres = %s\n", res);
	free(res);
	return ;
}

int	heredoc(char *eof)
{
	heredoc_loop(eof);
	return (0);
}
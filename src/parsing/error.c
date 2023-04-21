/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:16 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/21 08:31:55 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_heredoc_warning(char *token)
{
	ft_putstr_fd("Gigabash: warning: here-document delimi", STDERR_FILENO);
	ft_putstr_fd("ted by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	return (0);
}

int	print_linux_error(char *token)
{
	g_err_no = 1;
	ft_putstr_fd("Gigabash: ", STDERR_FILENO);
	perror(token);
	return (0);
}

int	print_bash_error(char *token, int errnum)
{
	g_err_no = errnum;
	if (errnum == 1)
	{
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(": something went wrong :/\n", STDERR_FILENO);
	}
	if (errnum > 2 && errnum < 126)
		return (print_linux_error(token));
	if (errnum == 2)
	{
		ft_putstr_fd("Gigabash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	if (errnum == 127)
	{
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (0);
}

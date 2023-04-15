/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:16 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/15 18:00:54 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error(char *token, int errnum)
{
	if (errnum > 2 && errnum < 126)
	{
		g_err_no = 1;
		ft_putstr_fd("Gigabash: ", 2);
		perror(token);
	}
	else
		g_err_no = errnum;
	if (errnum == 2)
	{
		ft_putstr_fd("Gigabash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (errnum == 127)
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (0);
}

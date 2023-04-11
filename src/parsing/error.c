/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:16 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/04 17:36:06 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_linux_error(char *token, int errnum)
{
	if (errnum == 2)
	{
		ft_putstr_fd("Gigabash: ", 2);
		perror(token);
	}
	return (1);
}

int	print_bash_error(char *token, int errnum)
{
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
	return (1);
}
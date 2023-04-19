/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:31:59 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/19 12:31:19 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(char *str)
{
	printf("%s", str);
	return (0);
}

int	str_has_only_dash_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	has_n_option(t_command *cmd)
{
	int	i;

	i = 1;
	while (str_has_only_dash_n(cmd->argv[i]) == 1)
		i++;
	return (i);
}

int	echo_controller(t_command *cmd)
{
	int	i;
	int	n_option;

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

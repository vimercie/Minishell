/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:41:05 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/15 20:59:57 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (0);
	while (1)
	{
		cmd = malloc(sizeof(t_command));
		cmd->cmd = readline("GigaBash$ ");
		parsing(cmd);
	}
	return (0);
}

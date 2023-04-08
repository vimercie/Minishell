/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:33:20 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/04 19:33:12 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void sigint_handler(int signum)
{	
	(void)signum;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

int signal_handling(struct sigaction sa, t_data *data)
{
	// if (!buffer)
	// {	
	// 	printf("_______________!BUFFER == TRUE________________\n");
	// 	exit(EXIT_SUCCESS);
	// }
    sa.sa_handler = &sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:33:20 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/18 01:28:22 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execve_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_err_no = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("TEST\n");
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	signal_handling(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	return (0);
}

int	signal_ignore(t_data *data)
{
	data->sa.sa_handler = SIG_IGN;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	sigaction(SIGINT, &data->sa, NULL);
	return (0);
}
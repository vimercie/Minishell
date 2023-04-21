/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:33:20 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/21 03:01:41 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_prompt_on_new_line(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', STDERR_FILENO);
	g_err_no = 130;
	exit(g_err_no);
}

void	prompt_on_new_line(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	heredoc_signal_handling(struct sigaction *sa)
{
	sa->sa_handler = heredoc_prompt_on_new_line;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	sa->sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	return (1);
}

int	child_signal_handling(struct sigaction *sa)
{
	sa->sa_handler = prompt_on_new_line;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	return (1);
}

int	exec_signal_handling(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	return (1);
}

int	signal_handling(struct sigaction *sa)
{
	sa->sa_handler = prompt_on_new_line;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGINT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	sa->sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, sa, NULL) == -1)
		return (print_linux_error("sigaction"));
	return (1);
}

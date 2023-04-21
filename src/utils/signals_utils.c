/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:26:19 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/21 08:27:22 by vimercie         ###   ########lyon.fr   */
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

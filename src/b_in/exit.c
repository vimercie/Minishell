/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:15:28 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/13 18:55:22 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	signal_return;

int	exit_bash(t_data *data, char *buffer)
{
	printf("exit bash\n");
	if (buffer)
		free(buffer);
	lst_free(data->env);
	exit(EXIT_SUCCESS);
}

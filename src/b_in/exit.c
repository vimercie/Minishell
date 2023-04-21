/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:15:28 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/21 08:07:44 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_bash(t_data *data, char *buffer)
{
	printf("exit bash\n");
	if (buffer)
		free(buffer);
	lst_free(data->env);
	free(data->tab_env);
	exit(g_err_no);
}

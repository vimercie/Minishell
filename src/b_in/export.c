/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/08 18:31:02 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <dirent.h>

int	export(char *str, t_env *env)
{
	t_env *lst_target;

	lst_target = lst_name(env, get_left_part(str));
//	printf("HERE\n");
	if (lst_target->next == NULL)
	{
		lst_target->next = malloc(sizeof(*lst_target));
		assign_name_value(lst_target, str);
		lst_target->next->next = NULL;
	}
	else
		assign_name_value(lst_target, str);
	return (0);
}
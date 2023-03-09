/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/10 00:08:16 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int		equal_index(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	assign_name_value(t_env *lst_new, char *string) 
{
	int i;
	int j;
	int e_i;

	i = 0;
	j = 0;
	e_i = equal_index(string);
	if (lst_new->value && e_i == -1)
		return (1);
	lst_new->name = calloc(sizeof(char), 32760);
	lst_new->value = calloc(sizeof(char), 32760);
	while (string[i] && string[i] != '=')
	{
		lst_new->name[i] = string[i];
		i++;
	}
	lst_new->name[i] = '\0';
	i++;
	while (string[i] != '\0')
	{
		lst_new->value[j] = string[i];
		i++;
		j++;
	}
	lst_new->value[j] = '\0';
	if (e_i != -1)
		lst_new->val = 1;
	else
		lst_new->val = 0;
	return (0);
}

int	export(char *str, t_env *env)
{
	t_env *lst_target;

	lst_target = lst_name(env, get_left_part(str));
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

int export_controller(t_command *cmd, t_env *env)
{
		int i;

	i = 1;
	while (i < cmd->d.n_arg)
	{
		export(cmd->argv[i], env);
		i++;
	}
	return (0);
}
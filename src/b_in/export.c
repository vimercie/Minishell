/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/09 15:09:11 by mmajani          ###   ########lyon.fr   */
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

	i = 0;
	j = 0;
	if (lst_new->value && equal_index(string) == -1)
		return (1);
	lst_new->name = malloc(sizeof(char) * 32760);
	lst_new->value = malloc(sizeof(char) * 32760);
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
	if (equal_index(string) != -1)
		lst_new->val = 1;
	else
	{
		
		lst_new->val = 0;
	}
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

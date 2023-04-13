/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/13 18:16:46 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	memory_handling(t_env *current, char *name, char *value)
{
	if (current->value && value == NULL)
	{
		free(name);
		return (1);
	}
	if (current->name == NULL)
		current->name = calloc(sizeof(char), 32760);
	if (current->value == NULL)
		current->value = calloc(sizeof(char), 32760);
	if (current->name == NULL || current->value == NULL)
	{
		free(name);
		free(value);
		return (1);
	}
	return (0);
}

int	assign_name_value(t_env *lst_new, char *string)
{
	char	*name;
	char	*value;

	name = get_env_name(string);
	value = get_env_value(string);
	if (memory_handling(lst_new, name, value) == 1)
		return (1);
	ft_strlcpy(lst_new->name, name, ft_strlen(name) + 1);
	free(name);
	if (value)
	{
		ft_strlcpy(lst_new->value, value, ft_strlen(value) + 1);
		lst_new->val = 1;
	}
	else
		lst_new->val = 0;
	free(value);
	return (0);
}

int	export(char *str, t_env *env)
{
	t_env	*lst_target;
	char	*left_part;

	left_part = get_left_part(str);
	lst_target = lst_name(env, left_part);
	if (lst_target->next == NULL)
	{
		lst_target->next = malloc(sizeof(*lst_target));
		lst_target->next->next = NULL;
		assign_name_value(lst_target, str);
	}
	else
		assign_name_value(lst_target, str);
	free(left_part);
	return (0);
}

int	export_controller(t_command *cmd, t_env *env)
{
	int	i;

	i = 1;
	while (i < cmd->d.n_arg)
	{
		export(cmd->argv[i], env);
		i++;
	}
	return (0);
}

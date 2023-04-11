/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:41:17 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/11 14:12:54 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*t_env_to_str(t_env *env)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char)
			* ft_strlen(env->name) + ft_strlen(env->value) + 2);
	while (i < ft_strlen(env->name) - 1)
	{
		str[i] = env->name[i];
		i++;
	}
	str[i] = '=';
	i++;
	while (j < ft_strlen(env->value))
		str[i++] = env->value[j++];
	str[i] = '\0';
	return (str);
}

char	**lst_env_to_tab_env(t_env *env)
{
	int		i;
	int		size;
	char	**new_env;
	t_env	*current;

	size = 0;
	current = env;
	while (current->next != NULL && size++ > -1)
		current = current->next;
	new_env = calloc(sizeof(char *), size + 2);
	i = 0;
	current = env;
	while (i < size)
	{
		new_env[i] = t_env_to_str(current);
		i++;
	}
	return (new_env);
}

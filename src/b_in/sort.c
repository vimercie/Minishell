/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:05:46 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/19 11:25:03 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	index_env(t_env *env)
{
	t_env	*elem;
	t_env	*next;

	elem = env;
	while (elem->next)
	{
		elem->index = 1;
		next = env;
		while (next->next != NULL)
		{
			if (elem->name && next->name
				&& ft_strcmp(elem->name, next->name) > 0)
				elem->index++;
			next = next->next;
		}
		elem = elem->next;
	}
}

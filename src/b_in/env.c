/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:12:18 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/19 17:29:49 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*lst_init_env(void)
{
	t_env	*start;

	start = malloc(sizeof(*start));
	start->name = NULL;
	start->value = NULL;
	start->val = 1;
	start->next = NULL;
	return (start);
}

t_env	*lst_name(t_env *lst, char *to_find)
{
	t_env	*next;

	if (lst == NULL)
		return (NULL);
	next = lst;
	while (next->next != NULL)
	{
		if (strncmp(next->name, to_find, ft_strlen(next->name)) == 0)
			return (next);
		next = next->next;
	}
	next->next = lst_init_env();
	print_list(next);
	return (next);
}

t_env	*lst_getenv(char **env)
{
	t_env	*lst_start;
	t_env	*lst_new;
	int		i;

	lst_start = lst_init_env();
	lst_new = lst_start;
	i = 0;
	while (env[i] != NULL)
	{
		lst_new->value = NULL;
		lst_new->name = NULL;
		assign_name_value(lst_new, env[i]);
		lst_new->next = calloc(sizeof(*lst_new), 1);
		lst_new = lst_new->next;
		i++;
	}
	lst_new->name = NULL;
	lst_new->value = NULL;
	lst_new->next = NULL;
	return (lst_start);
}

void	lst_free(t_env *lst)
{
	t_env	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

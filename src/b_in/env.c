/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:12:18 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/08 15:04:23 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_copyenv(char **env)
{
	char	**copy_env;
	int		nb_env;
	int		i;
	int		j;
	
	nb_env = 0;
	while (env[nb_env] != NULL)
		nb_env++;
	copy_env = malloc(sizeof(char *) * (nb_env + 1));
	if (copy_env == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < nb_env)
	{
		copy_env[i] = strdup(env[i]);
		if (copy_env[i] == NULL)
		{
			j = 0;
			while (j < i)
				free(copy_env[j++]);
			free(copy_env);
			return (NULL);
		}
		i++;
	}
	copy_env[nb_env] = NULL;    
	return (copy_env);
}

t_env    *lst_init_env(void)
{
	t_env   *start;

	start = malloc(sizeof(*start));
	start->name = NULL;
	start->value = NULL;
	start->val = 1;
	start->next = NULL;
	return (start);
}

void assign_name_value(t_env *lst_new, char *string) 
{
	int i;
	int j;

	i = 0;
	j = 0;
	lst_new->name = malloc(sizeof(char) * 32760);
	lst_new->value = malloc(sizeof(char) * 32760);
	while (string[i] != '=') {
		lst_new->name[i] = string[i];
		i++;
	}
	lst_new->name[i] = '\0';
	i++;
	while (string[i] != '\0') {
		lst_new->value[j] = string[i];
		i++;
		j++;
	}
	lst_new->value[j] = '\0';
	lst_new->val = 1;
}

t_env   *lst_name(t_env *lst, char *to_find)
{
	t_env *next;

	if (lst == NULL)
		return NULL;
	next = lst;
	while (next->next != NULL)
	{
		if (strncmp(next->name, to_find, ft_strlen(to_find)) == 0)
			return (next);
		next = next->next;
	}
	return (next);
}

t_env   *lst_getenv(char **env)
{
	t_env	*lst_start;
	t_env	*lst_new;
	int i;
	
	lst_start = lst_init_env();
	lst_new = lst_start;
	i = 0;
	while (env[i] != NULL)
	{
		assign_name_value(lst_new, env[i]);
		lst_new->next = malloc(sizeof(*lst_new));
		lst_new = lst_new->next;
		i++;
	}
	lst_new->next = NULL;
	return (lst_start);
}

char	*concat(t_env *env, char *str)
{
	t_env *var;
	char *tmp;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
			var = lst_name(env, "tout a droite du dollar ou la fin de la string");
		strcpy(tmp, var->value);
	}
	return (tmp);
}
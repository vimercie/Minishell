/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:30:05 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/21 08:06:05 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/minishell.h"

int	count_env(t_env *start)
{
	t_env	*head;
	int		count;

	count = 0;
	head = start;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

void	print_subft(t_env *current)
{
	printf("declare -x %s", current->name);
	if (current->val == 1)
		printf("=\"%s\"", current->value);
	printf("\n");
}

void	print_sorted_list(t_env *env)
{
	int		i;
	t_env	*current;

	index_env(env);
	i = 1;
	while (i <= count_env(env))
	{
		current = env;
		while (current->next)
		{
			if (i == current->index)
			{
				if (ft_strncmp(current->name, "_", 2) == 0)
				{
					i++;
					current = current->next;
					continue ;
				}
				print_subft(current);
			}
			current = current->next;
		}
		i++;
	}
}

int	print_list(t_env *env)
{
	int		i;
	t_env	*current;
	int		size;

	i = 1;
	current = env;
	size = count_env(env);
	while (i < size - 1)
	{
		while (current->next)
		{
			if (current->val == 1)
			{
				printf("%s", current->name);
				printf("=%s", current->value);
			}
			printf("\n");
			current = current->next;
		}
		i++;
	}
	return (0);
}

char	*get_left_part(char *string)
{
	int		i;
	int		j;
	char	*left_part;

	left_part = malloc((strlen(string) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (string[i] && string[i] != '=')
	{
		left_part[j] = string[i];
		i++;
		j++;
	}
	left_part[j] = '\0';
	return (left_part);
}

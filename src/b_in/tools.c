/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:30:05 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/08 14:29:36 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/minishell.h"

void print_env(char **env)
{
    char **envp = env;

    while (*envp != NULL)
	{
        printf("declare -x ");
        printf("%s\n", *envp);
        envp++;
    }
}

int	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current->next != NULL)
	{
		printf("declare -x %s", current->name);
		if (current->val == 1)
			printf("=\"%s\"\n", current->value);
		current = current->next; 
	}
	return (1);
}

char *get_left_part(char *string)
{
    int i;
    int j;
    char *left_part;
    
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
    return left_part;
}

// int print_ascii_order_env(char **env)
// {
// 	int i;
// 	int j;
// 	char *tmp;
	
// 	i = 0;
// 	while (env[i + 1] != NULL)
// 	{
// 		j = i + 1;
// 		while (env[j] != NULL)
// 		{
// 			if (strcmp(env[i], env[j]) > 0) {
// 				tmp = env[i];
// 				env[i] = env[j];
// 				env[j] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (env[i + 1] != NULL)
// 		printf("declare -x %s\n", env[i++]);
// 	return (0);
// }

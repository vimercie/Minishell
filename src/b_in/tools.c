/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:30:05 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/09 15:09:17 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/minishell.h"

void swap_elements(t_env *ptr1, t_env *ptr2)
{
	char *temp_name;
	char *temp_value;
	int temp_val;

	temp_name = ptr1->name;
	temp_value = ptr1->value;
	temp_val = ptr1->val;
	ptr1->name = ptr2->name;
	ptr1->value = ptr2->value;
	ptr1->val = ptr2->val;
	ptr2->name = temp_name;
	ptr2->value = temp_value;
	ptr2->val = temp_val;
}

void sort_list_ascii(t_env **head)
{
	t_env *ptr1;
	t_env *ptr2;

	ptr1 = *head;
	while (ptr1->next != NULL)
	{
		ptr2 = ptr1->next;
		while (ptr2 != NULL)
		{
			if (strcmp(ptr1->name, ptr2->name) > 0)
				swap_elements(ptr1, ptr2);
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

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
        else
            printf("\n");
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
    return (left_part);
}

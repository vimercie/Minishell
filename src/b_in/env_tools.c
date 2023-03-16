/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:21:22 by mmajani           #+#    #+#             */
/*   Updated: 2023/03/16 15:38:38 by mmajani          ###   ########lyon.fr   */
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

char *get_env_name(char *string)
{
    int i = 0;
    char *name = calloc(sizeof(char), 32760);

    while (string[i] && string[i] != '=') {
        name[i] = string[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

char *get_env_value(char *string)
{
    int i = 0;
    int e_i = equal_index(string);
    char *value = NULL;

    if (e_i != -1)
	{
        value = calloc(sizeof(char), 32760);
        i = e_i + 1;
        int j = 0;
        while (string[i])
            value[j++] = string[i++];
        value[j] = '\0';
    }
    return (value);
}

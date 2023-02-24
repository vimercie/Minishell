/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:30:05 by mmajani           #+#    #+#             */
/*   Updated: 2023/02/23 15:30:22 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/minishell.h"

char* getShellName() {
	char* shellName = getenv("SHELL");
	if (shellName == NULL) {
		perror("Erreur : impossible de trouver le shell");
		exit(1);
	}
	int lastSlashIndex = 0;
	for (int i = 0; i < strlen(shellName); i++) {
		if (shellName[i] == '/') {
			lastSlashIndex = i;
		}
	}
	shellName[lastSlashIndex] = '\0';
	return &shellName[lastSlashIndex + 1];
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

void print_ascii_order_env(char **env)
{
	int i;
	char *tmp;
	
	i = 0;
	while (env[i] != NULL)
	{
		int j = i + 1;
		while (env[j] != NULL)
		{
			if (strcmp(env[i], env[j]) > 0) {
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i] != NULL)
		printf("declare -x %s\n", env[i++]);
}


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
        return NULL;
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
            return NULL;
        }
		i++;
	}
    copy_env[nb_env] = NULL;    
    return (copy_env);
}

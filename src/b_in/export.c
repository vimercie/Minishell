/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/02/27 12:18:49 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <dirent.h>

int	ft_putenv(char *name, char *value, char **env)
{
	int i;
	char *tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (strlen(name) + strlen(value) + 2));
	if (!(tmp))
		return (1);
	strcpy(tmp, name);
	strcat(tmp, "=");
	strcat(tmp, value);
	while (env[i])
		i++;
	env[i] = malloc(sizeof(char) * (strlen(name) + strlen(value) + 2));
	if (!(env[i]))
		return (1);
	strcpy(env[i], tmp);
	env[i + 1] = NULL;
	return (0);
}

int export(char *str, char **envp)
{
	t_env	var;
	char	*equalSign = strchr(str, '=');
  	int		equalSignPosition = equalSign - str;

	// Allouer la mémoire nécessaire pour le nom et la valeur 
	var.name = malloc(equalSignPosition + 1);
	var.value = malloc(strlen(str) - equalSignPosition);

	// Copier le nom et la valeur dans les variables respectives
	strncpy(var.name, str, equalSignPosition);
	strcpy(var.value, equalSign + 1);
	var.name[equalSignPosition] = '\0';

	// Ajouter la variable à l'environnement
	if (ft_putenv(var.name, var.value, envp) == 1)
		return (1);
	else
	{
		printf("NOPE\n");
		// print_ascii_order_env(envp);
		return (0);
	}
	return (0);
}

// int main(int ac, char **av, char **envp)
// {

//     export(av[1], envp);
//     return 0;
// }

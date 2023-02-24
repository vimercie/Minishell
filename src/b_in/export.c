/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:50:43 by mmajani           #+#    #+#             */
/*   Updated: 2023/02/24 13:21:24 by vimercie         ###   ########lyon.fr   */
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
		return (-1);
	strcpy(tmp, name);
	strcat(tmp, "=");
	strcat(tmp, value);
	while (env[i])
		i++;
    env[i] = malloc(sizeof(char) * (strlen(name) + strlen(value) + 2));
	if (!(env[i]))
		return (-1);
	strcpy(env[i], tmp);
	env[i + 1] = NULL;
	return (0);
}

int	export_with_value(char *str, char **env)
{
	char *name;
	char *value;
	int i;

	i = 0;
	printf("exporting \"%s\" to env", str);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (1);
    name = malloc(sizeof(char) * (i + 1));
	if (!(name))
		return (1);
	strncpy(name, str, i);
	name[i] = '\0';
	value = str + i + 1;
	if (ft_putenv(name, value, env) == -1)
		return (1);
	free(name);
	return (0);
}

int export(char *str, char **envp)
{	
	if (str)
	{
		export_with_value(str, envp);
		return (1);
	}
	else
	{
		printf("NOPE\n");
		print_ascii_order_env(envp);
		return (0);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{

    export(av[1], envp);
    return 0;
}
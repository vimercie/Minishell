#include "../inc/minishell.h"

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

int	export(char *str, char **env)
{
	char *name;
	char *value;
	int i;

	i = 0;
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

// int main(int argc, char **argv, char **envp)
// {
// 	int i;
//     char** env;
//     env = ft_copyenv(envp);

// 	if (argc < 2)
// 	{
// 		printf("usage: export <variable>=<value>\n");
// 		return (1);
// 	}
// 	if (export(argv[1], env))
// 	{
// 		printf("Error: unable to export environment variable\n");
// 		return (1);
// 	}
// 	printf("Exported environment variable:\n");
// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
//     // free(env[0]);
//     free(env[i - 1]);
// 	return (0);
// }
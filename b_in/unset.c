#include "../inc/minishell.h"

int	unsetenv(char *name, char **env)
{
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0 && env[i][strlen(name)] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

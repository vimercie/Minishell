#include "../../inc/minishell.h"

int	get_current_dir(void)
{
	char *cwd;

	// Get the current working directory
	cwd = (char *)malloc(sizeof(char) * 1024);
	if (!cwd)
		return (0);
	getcwd(cwd, sizeof(char) * 1024);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

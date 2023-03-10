#include "../../inc/minishell.h"


void	lst_del(t_env *lst, char *to_find)
{
	t_env *prev;
	t_env *next;

	if (lst == NULL)
		return ;
	prev = lst;
	next = lst_name(lst, to_find);
	if (next == NULL)
		return ;
	while (prev->next != next)
	{
		prev = prev->next;
	}
	prev->next = next->next;
	free(next->name);
	free(next->value);
	free(next);
}

int		unset_var(t_command *cmd, t_env *env)
{
	int i;

	i = 1;
	while (i < cmd->d.n_arg)
	{
		lst_del(env, cmd->argv[i]);
		i++;
	}
	return (0);
}


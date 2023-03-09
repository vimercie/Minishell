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

void		lst_free(t_env *lst)
{
	t_env *prev;
	t_env *current;

	if (lst == NULL)
		return ;
	prev = lst;
	current = lst->next;
	while (current != NULL)
	{
		lst_del(lst, current->name);
		current = current->next;
		prev = prev->next;
	}
	free(prev->name);
	free(prev->value);
	free(prev);
}

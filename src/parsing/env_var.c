/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:59:23 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/14 16:41:08 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env_var_value(char *to_find, t_env *env)
{
	t_env	*current;

	if (!env || !to_find)
		return (NULL);
	current = env;
	while (current->next)
	{
		if (ft_strcmp(to_find, current->name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

char	*replace_env_var(char *input, int *index, t_env *env)
{
	char	*res;
	char	*name;
	int		i;

	i = 0;
	if (input[0] == '$')
	{
		i++;
		while (!is_metachar(input[i]) && input[i])
			i++;
		name = ft_strndup(input, i);
		res = find_env_var_value(name + 1, env);
		free(name);
	}
	else
	{
		while ((input[i] != '$' || is_quoted(input, i) == 1) && input[i])
			i++;
		res = ft_strndup(input, i);
	}
	*index += i;
	return (res);
}

char	*handle_env_var(char *input, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*value;
	int		i;

	if (!input)
		return (NULL);
	res = NULL;
	if (is_quote(input, 0) == 1)
		return (ft_strdup(input));
	while (input[0])
	{
		i = 0;
		value = replace_env_var(input, &i, env);
		input += i;
		tmp = ft_strdup(res);
		free(res);
		res = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
	}
	return (res);
}

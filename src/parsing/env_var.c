/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:59:23 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/18 02:08:12 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env_var_value(char *to_find, t_env *env)
{
	t_env	*current;

	if (!env || !to_find)
		return (NULL);
	if (ft_strcmp(to_find, "?") == 0)
		return (ft_itoa(g_err_no));
	current = env;
	while (current->next)
	{
		if (ft_strcmp(to_find, current->name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

char	*name_to_env(char *input, int *index, t_env *env)
{
	char	*name;
	char	*res;

	while (!is_metachar(input[*index]) && !ft_isspace(input[*index])
		&& *index == 0 && input[*index])
		*index += 1;
	name = ft_strndup(input, *index);
	res = find_env_var_value(name + 1, env);
	free(name);
	return (res);
}

char	*replace_env_var(char *input, int *index, t_env *env)
{
	char	*res;
	int		i;

	i = 0;
	if (input[0] == '$')
	{
		if (!input[1])
		{
			*index += 1;
			return (ft_strdup(input));
		}
		res = name_to_env(input, &i, env);
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
	if (is_quote(input, 0) == 1
		|| ft_strcmp(input, "\"$\"") == 0)
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

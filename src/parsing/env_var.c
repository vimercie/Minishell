/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:59:23 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/10 01:20:44 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_env_var(char *input, t_env *env)
{
	t_env	*lst;
	char	*res;
	char	*tmp;
	char	*var_name;
	int		i;

	res = NULL;
	while (input[0])
	{
		i = 0;
		var_name = NULL;
		tmp = ft_strdup(res);
		free(res);
		if (input[0] == '$')
		{
			input++;
			while (!is_metachar(input[i]) && input[i])
				i++;
			var_name = ft_strndup(input, i);
			lst = lst_name(env, var_name);
			if (lst->value && tmp)
				res = ft_strjoin(tmp, lst->value);
			else if (!lst->value)
				res = ft_strdup(tmp);
			else if (!tmp)
				res = ft_strdup(lst->value);
		}
		else
		{
			while (input[i] != '$' && input[i])
				i++;
			var_name = ft_strndup(input, i);
			if (tmp)
				res = ft_strjoin(tmp, var_name);
			else
				res = ft_strdup(var_name);
		}
		free(tmp);
		free(var_name);
		input += i;
	}
	return (res);
}

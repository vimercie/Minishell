/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:59:23 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/08 16:59:33 by vimercie         ###   ########lyon.fr   */
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
	tmp = NULL;
	var_name = NULL;
	while (input[0])
	{
		i = 0;
		if (res)
			tmp = ft_strdup(res);
		else
			tmp = ft_calloc(1, sizeof(char));
		free(res);
		if (input[0] == '$')
		{
			input++;
			while (!is_metachar(input[i]) && input[i])
				i++;
			var_name = ft_strndup(input, i);
			lst = lst_name(env, var_name);
			if (lst)
				res = ft_strjoin(tmp, lst->value);
		}
		else
		{
			while (input[i] != '$' && input[i])
				i++;
			var_name = ft_strndup(input, i);
			res = ft_strjoin(tmp, var_name);
		}
		free(tmp);
		free(var_name);
		input += i;
	}
	printf("res = |%s|\n", res);
	return (res);
}

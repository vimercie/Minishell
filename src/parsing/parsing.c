/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/06 13:27:12 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/_types/_id_t.h>

char	*clean_input(char *input)
{
	int		input_len;
	char	*res;
	int		i;
	int		j;

	input_len = ft_strlen(input);
	res = malloc(input_len * sizeof(char));
	ft_memset(res, '\0', input_len);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\\')
			i++;
		else if (input[i] == ' ')
		{
			res[j] = input[i];
			while (input[i] == ' ')
				i++;
			j++;
		}
		else
			res[j] = input[i];
			i++;
			j++;
	}
	return (res);
}

// int	isPath(char *input)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	while (path[i] != ' ')
// 		i++;
// 	path = ft_substr(input, 0, i);
// 	return (0);
// }

int	parsing(char *input)
{
	// t_command	cmd;
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			skip_ws(input + i);
		else if (input[i] == '\\')
			i++;
		// else if (input[i] == '/')
		// 	isPath(input + i);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/07 00:39:19 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*input_cleaner(char *input)
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
		if (input[i] == ' ' || input[i] == '\\')
			res = skip_junk(input, res, &i, &j);
		else
		{
			res[j] = input[i];
			i++;
			j++;
		}
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
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->cmd = input_cleaner(input);
	printf("input \t= \"%s\"\n", input);
	printf("cmd \t= \"%s\"\n", cmd->cmd);
	free(cmd->cmd);
	return (0);
}

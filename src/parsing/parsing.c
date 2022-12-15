/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/15 21:17:15 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*manage_quote(char *input, char *res, int *i, int *j)
{
	int	index;

	index = *i + 1;
	while (input[index] != input[*i] && input[index])
		index++;
	if (input[index] == input[*i] && index != *i + 1 && input[index])
	{
		while (*i <= index)
		{
			res[*j] = input[*i];
			*i += 1;
			*j += 1;
		}
	}
	else
		*i += 1;
	return (res);
}

char	*skip_junk(char *input, char *res, int *i, int *j)
{
	int	ws;
	int	start_i;

	ws = 0;
	start_i = *i;
	while (is_junk(input + *i))
	{
		if (input[*i] == ' ' && ws == 0)
			ws = 1;
		*i += 1;
	}
	if (ws == 1 && start_i != 0 && input[*i])
	{
		res[*j] = ' ';
		*j += 1;
	}
	return (res);
}

char	*input_cleaner(char *input)
{
	int		input_len;
	char	*res;
	int		i;
	int		j;

	input_len = ft_strlen(input);
	res = malloc((input_len * sizeof(char)) + 1);
	ft_memset(res, '\0', input_len + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_junk(input + i))
			res = skip_junk(input, res, &i, &j);
		else if (is_quote(input + i))
			res = manage_quote(input, res, &i, &j);
		else
		{
			res[j] = input[i];
			i++;
			j++;
		}
	}
	free(input);
	return (res);
}

int	parsing(char *cmd)
{
	printf("input \t= |%s|\n", cmd);
	cmd = input_cleaner(cmd);
	printf("cmd \t= |%s|\n", cmd);
	free(cmd);
	return (0);
}

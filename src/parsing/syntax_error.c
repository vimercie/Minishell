/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/22 19:55:17 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*skip_ws(char *input, int *i, int *j)
{
	int	ws;
	int	start_i;

	ws = 0;
	start_i = *i;
	while (ft_isspace(input[*i]))
	{
		ws = 1;
		*i += 1;
	}
	if (ws == 1 && start_i != 0 && input[*i])
	{
		input[*j] = ' ';
		*j += 1;
	}
	return (input);
}

char	*syntax_cleaner(char *input)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (input[i])
	{
		if (ft_isspace(input[i]) && !is_in_quotes(input, i))
		{
			if (is_command(input + i))
			{
				res[j] = ' ';
				j++;
			}
			while (ft_isspace(input[i]) && input[i])
				i++;
		}
		// else if (is_meta_char(input[i]) && !is_in_quotes(input, i))
		// {
			
		// }
		else
		{
			res[j] = input[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	free(input);
	return (res);
}

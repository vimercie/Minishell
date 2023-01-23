/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/23 03:28:15 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

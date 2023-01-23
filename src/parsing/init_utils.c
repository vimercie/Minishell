/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:54:47 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/23 02:54:57 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_quotes(char *s)
{
	char	*res;
	int		n_quote;
	int		i;
	int		j;

	i = 0;
	n_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && !is_in_quotes(s, i)
			&& is_in_quotes(s, i + 1) + is_in_quotes(s, i - 1) == 1)
			n_quote++;
		i++;
	}
	res = ft_calloc(i - n_quote + 1, sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] != '\"' && s[i] != '\'') || is_in_quotes(s, i)
			|| (!is_in_quotes(s, i + 1) && !is_in_quotes(s, i - 1)))
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	return (res);
}

int		get_n_arg(char *input)
{
	int	n_arg;
	int	i;

	i = 0;
	n_arg = 0;
	while (ft_isspace(input[i]) && input[i])
		i++;
	while (input[i])
	{
		if (ft_isspace(input[i]) && !is_in_quotes(input, i))
		{
			if (is_command(input + i))
			{
				n_arg++;
				while (ft_isspace(input[i]) && input[i])
					i++;
			}
			else
				return (n_arg);
		}
		else
			i++;
	}
	return (n_arg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:02:24 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/07 18:41:56 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_metachar(char c)
{
	if (c == '\''
		|| c == '\"'
		|| c == '>'
		|| c == '<'
		|| c == '$')
		return (1);
	return (0);
}

int	is_command(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_quote(char *s, int index)
{
	if ((s[index] == '\"' || s[index] == '\'') && !is_quoted(s, index)
		&& (is_quoted(s, index + 1) + is_quoted(s, index - 1) == 1
		|| (s[index + 1] == s[index] || s[index - 1] == s[index])))
		return (1);
	return (0);
}

int	is_quoted(char *s, int index)
{
	int	opening_quote_index;
	int	in_quote;
	int	i;

	i = 0;
	while (s[i])
	{
		in_quote = 0;
		opening_quote_index = i;
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			while (s[i] != s[opening_quote_index] && s[i])
			{
				if (i == index)
					in_quote = 1;
				i++;
			}
			if (s[i] == s[opening_quote_index] && in_quote)
				return (1);
		}
		i++;
	}
	return (0);
}

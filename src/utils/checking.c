/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:02:24 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/14 15:54:39 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_metachar(char c)
{
	if (c == '|'
		|| c == '\''
		|| c == '\"'
		|| c == '>'
		|| c == '<'
		|| c == '$')
		return (1);
	return (0);
}

int	is_string_blank(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_quote(char *s, int index)
{
	if (!s || !s[index])
		return (0);
	if ((s[index] == '\"' || s[index] == '\'')
		&& !is_quoted(s, index)
		&& ((is_quoted(s, index + 1) || is_quoted(s, index - 1))
			|| (s[index + 1] == s[index] || s[index - 1] == s[index])))
	{
		if (s[index] == '\'')
			return (1);
		else
			return (2);
	}
	return (0);
}

int	is_quoted(char *s, int index)
{
	int	opening_quote_index;
	int	is_dquote;
	int	res;
	int	i;

	i = 0;
	while (s[i])
	{
		res = 0;
		is_dquote = 0;
		opening_quote_index = i;
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (s[i] == '\"')
				is_dquote = 1;
			i++;
			while (s[i] != s[opening_quote_index] && s[i])
			{
				if (i == index)
					res = 1;
				i++;
			}
			if (s[i] == s[opening_quote_index] && res == 1)
				return (res + is_dquote);
		}
		i++;
	}
	return (0);
}

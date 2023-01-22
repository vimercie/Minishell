/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:12:21 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/22 06:25:33 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_meta_char(char c)
{
	if (c == '>'
		|| c == '<'
		|| c == '$'
		|| c == '?')
		return (1);
	return (0);
}

int	is_prompt(char *s)
{
	int	is_prompt;
	int	i;

	is_prompt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			if (!is_command(s + i + 1))
				is_prompt = 1;
		}
		i++;
	}
	return (is_prompt);
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

int	is_quote(char *s)
{
	if (s[0] == '\'' || s[0] == '\"')
		return (1);
	return (0);
}

int	is_in_quotes(char *s, int index)
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

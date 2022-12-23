/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:12:21 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 17:52:55 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_command(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_junk(s + i))
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
	int	i;
	int	first_quote;
	int	last_quote;

	if (index <= 0)
		return (0);
	i = 0;
	first_quote = 0;
	last_quote = 0;
	while (s[i] && last_quote == 0)
	{
		if (is_quote(s + i))
		{
			if (i < index)
				first_quote = 1;
			if (i > index)
				last_quote = 1;
		}
		i++;
	}
	if (first_quote == 1 && last_quote == 1)
		return (1);
	return (0);
}

int	is_junk(char *s)
{
	if (s[0] == ' ' || s[0] == '\t' || s[0] == '\\')
		return (1);
	return (0);
}

int	is_ws(char *s)
{
	if (s[0] == ' ' || s[0] == '\t')
		return (1);
	return (0);
}

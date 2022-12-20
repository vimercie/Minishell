/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/20 00:20:05 by vimercie         ###   ########.fr       */
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

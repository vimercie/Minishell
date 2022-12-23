/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 19:52:39 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*gather_full_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (full_path);
}

char	*remove_quotes(char *s)
{
	char	*res;
	int		n_quote;
	int		i;
	int		len;

	i = 0;
	n_quote = 0;
	while (s[i])
	{
		if (is_quote(s + i))
			n_quote++;
		i++;
	}
	len = i - n_quote;
	res = ft_calloc(len + 1, sizeof(char));
	i = 0;
	len = 0;
	while (s[i])
	{
		if (!is_quote(s + i))
		{
			res[len] = s[i];
			len++;
		}
		i++;
	}
	free(s);
	return (res);
}

int	count_pipes(char *input)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (is_command(input + i + 1))
				res++;
			else
				printf("readline = %s\n", readline("pipe> "));
		}
		i++;
	}
	return (res);
}

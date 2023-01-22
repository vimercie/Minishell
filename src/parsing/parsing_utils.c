/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/13 02:36:47 by vimercie         ###   ########.fr       */
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

int	cmd_count(char *s, char c)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	while (s[i])
	{
		if (s[i] == c
			&& s[i + 1] != c
			&& s[i - 1] != c)
		{
			if(!is_command((s + i) + 1))
				return (res);
			res++;
		}
		i++;
	}
	return (res);
}

char	*get_next_word(char *s, char c, int *i)
{
	char	*str;
	int		start;

	start = *i;
	while (s[*i])
	{
		if (s[*i] == c)
		{
			if (s[*i + 1] != c && s[*i - 1] != c)
				break ;
			*i += 1;
		}
		*i += 1;
	}
	str = ft_substr(s, start, *i - start);
	*i += 1;
	return (str);
}

char	**custom_split(char *s, char c, int n_cmd)
{
	char	**tab;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	tab = ft_calloc(n_cmd + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < n_cmd)
	{
		tab[j] = get_next_word(s, c, &i);
		if (!tab[j])
		{
			free_tab(tab);
			return (NULL);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	*str_trunc(char *s, int start, int end)
{
	char	*res;
	char	*first_part;
	char	*last_part;
	int		len;

	if (!s[0])
		return (NULL);
	len = ft_strlen(s);
	first_part = NULL;
	last_part = NULL;
	if (start > 0)
	{
		if (start < len)
			first_part = ft_substr(s, 0, start);
		else
			return (ft_substr(s, 0, len));
		if (end < len)
			last_part = ft_substr(s, end, len);
		else
			return (first_part);
	}
	else
	{
		if (end < len)
			return (ft_substr(s, end, len));
		else
			return (ft_strdup(s));
	}
	res = ft_strjoin(first_part, last_part);
	free(first_part);
	free(last_part);
	return (res);
}

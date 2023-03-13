/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/13 17:21:43 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_count(char *s, char c)
{
	int		i;
	int		res;

	i = 0;
	res = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c
			&& s[i + 1] != c
			&& s[i - 1] != c)
		{
			if(is_string_blank((s + i) + 1))
				return (res);
			res++;
		}
		i++;
	}
	return (res);
}

// char	*get_next_word(char *s, char c, int *i)
// {
// 	char	*str;
// 	int		start;

// 	start = *i;
// 	while (s[*i])
// 	{
// 		if (s[*i] == c)
// 		{
// 			if (s[*i + 1] != c && s[*i - 1] != c)
// 				break ;
// 			*i += 1;
// 		}
// 		*i += 1;
// 	}
// 	str = ft_substr(s, start, *i - start);
// 	*i += 1;
// 	return (str);
// }

// char	**custom_split(char *s, char c, int n_cmd)
// {
// 	char	**tab;
// 	int		i;
// 	int		j;

// 	tab = ft_calloc(n_cmd + 1, sizeof(char *));
// 	if (tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (j < n_cmd)
// 	{
// 		tab[j] = get_next_word(s, c, &i);
// 		if (!tab[j])
// 		{
// 			free_tab(tab);
// 			return (NULL);
// 		}
// 		j++;
// 	}
// 	tab[j] = NULL;
// 	return (tab);
// }

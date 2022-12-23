/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:05:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 04:28:13 by vimercie         ###   ########.fr       */
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

// size_t	wordcount(char *s, char c)
// {
// 	size_t	i;
// 	size_t	res;

// 	i = 0;
// 	res = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && ((s[i + 1] == c && !is_in_quote(s, i)) || !s[i + 1]))
// 			res++;
// 		i++;
// 	}
// 	return (res);
// }

// char	**custom_split(char *s, char c)
// {
// 	char	**tab;
// 	size_t	n_word;
// 	size_t	len;
// 	size_t	i;

// 	if (s == NULL || s[0] == '\0')
// 		return (NULL);
// 	tab = ft_calloc(wordcount(s, c) + 1, sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	i = 0;
// 	n_word = 0;
// 	while (n_word < wordcount(s, c))
// 	{
// 		len = 0;
// 		if (!is_in_quote(s, i))
// 		{
// 			while (s[i] == c)
// 				i++;
// 		}
// 		while (s[i] && (s[i] != c || is_in_quote(s, i)))
// 		{
// 			i++;
// 			len++;
// 		}
// 		tab[n_word] = ft_substr(s + i, 0, len);
// 		if (!tab[n_word])
// 		{
// 			free_tab(tab);
// 			return (NULL);
// 		}
// 		n_word++;
// 	}
// 	tab[n_word] = NULL;
// 	return (tab);
// }

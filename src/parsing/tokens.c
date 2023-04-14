/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:11:15 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/14 18:58:47 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_tokens(char *input)
{
	int	n_token;
	int	len;

	len = 0;
	n_token = 0;
	while (!is_string_blank(input + len))
	{
		while (ft_isspace(input[len]) && input[len])
			len++;
		len += token_len(input + len);
		n_token++;
	}
	return (n_token);
}

int	handle_metachar(char *input)
{
	int	res;

	res = 1;
	if (input[0] == '$')
	{
		while (!ft_isspace(input[res])
			&& input[res] != '>' && input[res] != '<' && input[res] != '|'
			&& input[res])
			res++;
	}
	else if (input[0] == '<' || input[0] == '>')
	{
		if (input[1] == input[0])
			res++;
	}
	else if (input[0] == '\'' || input[0] == '\"')
	{
		while (is_quoted(input, res) != 0)
			res++;
		res++;
	}
	return (res);
}

int	token_len(char *input)
{
	int	res;

	res = 0;
	if (is_metachar(input[0]))
		res += handle_metachar(input);
	else
	{
		while (((input[res] != '<' && input[res] != '>'
					&& !ft_isspace(input[res])) || is_quoted(input, res))
			&& input[res])
			res++;
	}
	return (res);
}

char	**tokenize_input(char *input)
{
	char	**res;
	int		start;
	int		len;
	int		i;

	if (is_string_blank(input))
		return (NULL);
	i = 0;
	len = 0;
	res = ft_calloc(count_tokens(input) + 1, sizeof(char *));
	while (!is_string_blank(input + len))
	{
		while (ft_isspace(input[len]) && input[len])
			len++;
		start = len;
		len += token_len(input + len);
		res[i] = ft_substr(input, start, len - start);
		i++;
	}
	return (res);
}

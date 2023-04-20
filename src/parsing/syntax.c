/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/20 16:58:05 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quoted_string(char *input, int *i)
{
	if (is_quote(input, *i) && is_quoted(input, *i + 1))
	{
		*i += 1;
		while (is_quoted(input, *i))
			*i += 1;
	}
	else
		return (0);
	return (1);
}

int	check_quotes_closing(char *input)
{
	char	*token;
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (is_quote(input, i))
				skip_quoted_string(input, &i);
			else
			{
				token = ft_strndup(input + i, 1);
				print_bash_error(token, 2);
				free(token);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_consecutive_metachar(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<' || tokens[i][0] == '|')
		{
			if (is_string_blank(tokens[i + 1]))
				return (print_bash_error("newline", 2));
			if (tokens[i + 1][0] == '>' || tokens[i + 1][0] == '<'
				|| tokens[i + 1][0] == '|')
				return (print_bash_error(tokens[i + 1], 2));
		}
		i++;
	}
	return (1);
}

int	check_syntax(char *input, char **tokens)
{
	int		return_val;

	return_val = 1;
	if (!check_consecutive_metachar(tokens)
		|| !check_quotes_closing(input))
		return_val = 0;
	if (tokens[0][0] == '|')
		return_val = print_bash_error(tokens[0], 2);
	return (return_val);
}

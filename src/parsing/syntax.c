/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/08 02:27:09 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_consecutive_metachar(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (tokens[i + 1] == NULL)
				return (print_bash_error("newline", 2));
			if (tokens[i + 1][0] == '>' || tokens[i + 1][0] == '<'
				|| tokens[i + 1][0] == '|')
				return (print_bash_error(tokens[i + 1], 2));
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *input)
{
	char	**tokens;

	tokens = tokenize_input(input);
	if (!tokens)
		return (1);
	if (check_consecutive_metachar(tokens))
		return (0);
	free_tab(tokens);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/31 18:10:04 by vimercie         ###   ########lyon.fr   */
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
				return (write(2, "syntax error near unexpected token `newline'\n", 45) - 44);
			if (tokens[i + 1][0] == '>' || tokens[i + 1][0] == '<'
				|| tokens[i + 1][0] == '|')
			{
				write(2, "syntax error near unexpected token `", 36);
				ft_putstr_fd(tokens[i + 1], 2);
				write(2, "'\n", 2);
				return (1);
			}
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
	return (1);
}

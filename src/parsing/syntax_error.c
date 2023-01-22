/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:41 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/22 06:45:25 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_quotes(char *s)
{
	// re-work is planned (to make it work like the is_in_quote() func).
	char	*res;
	int		n_quote;
	int		len;
	int		i;

	i = 0;
	n_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && !is_in_quotes(s, i))
			n_quote++;
		i++;
	}
	len = i - n_quote;
	res = ft_calloc(len + 1, sizeof(char));
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\"' && s[i] != '\'' && !is_in_quotes(s, i))
		{
			res[len] = s[i];
			len++;
		}
		i++;
	}
	free(s);
	return (res);
}

char	*skip_ws(char *input, int *i, int *j)
{
	int	ws;
	int	start_i;

	ws = 0;
	start_i = *i;
	while (ft_isspace(input[*i]))
	{
		ws = 1;
		*i += 1;
	}
	if (ws == 1 && start_i != 0 && input[*i])
	{
		input[*j] = ' ';
		*j += 1;
	}
	return (input);
}

char	*syntax_cleaner(char *input)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (input[i])
	{
		if (ft_isspace(input[i]) && !is_in_quotes(input, i))
		{
			if (is_command(input + i))
			{
				res[j] = ' ';
				j++;
			}
			while (ft_isspace(input[i]) && input[i])
				i++;
		}
		else
		{
			res[j] = input[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	free(input);
	return (res);
}

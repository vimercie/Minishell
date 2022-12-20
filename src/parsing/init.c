/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/20 01:42:02 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	cmd_end_index(char *input)
{
	int		in_quotes;
	int		i;

	i = 0;
	in_quotes = 0;
	while (input[i])
	{
		if (is_quote(input + i))
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else
				in_quotes = 0;
		}
		else if (is_ws(input + i) && in_quotes == 0)
			break ;
		i++;
	}
	return (i);
}

char	**args_init(char *input)
{
	char	**res;
	int		n_cmd;
	int		i;
	int		j;
	int		k;

	i = 0;
	n_cmd = 0;
	while (input[i])
	{
		i += cmd_end_index(input + i);
		i++;
		n_cmd++;
	}
	res = ft_calloc(n_cmd + 1, sizeof(char *));
	i = 0;
	j = cmd_end_index(input);
	while (is_junk(input + j))
		j++;
	k = j;
	while (input[k])
	{
		k += cmd_end_index(input + j);
		res[i] = ft_substr(input, j, k);
		while (is_junk(input + j))
			j++;
		i++;
	}
	res[i][0] = '\0';
	return (res);
}

char		*cmd_init(char *input)
{
	char	*res;

	res = ft_substr(input, 0, cmd_end_index(input));
	return (res);
}

t_command	*data_init(char **pipe_split, int n_pipes)
{
	t_command	*cmd;
	char		*clean_input;
	int			i;

	i = 0;
	cmd = ft_calloc(n_pipes + 2, sizeof(t_command));
	while (i < n_pipes + 1)
	{
		clean_input = syntax_cleaner(pipe_split[i]);
		if (clean_input == NULL)
		{
			free(cmd);
			return (NULL);
		}
		// clean_input = replace_env_v(cmd);
		printf("input = %s\n", clean_input);
		cmd[i].cmd = cmd_init(clean_input);
		cmd[i].args = args_init(clean_input);
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		i++;
	}
	free(clean_input);
	cmd[i].cmd = NULL;
	return (cmd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/27 22:45:43 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_cmd_path(char *cmd)
{
	char	**path;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!cmd[0])
		return (res);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		res = gather_full_path(path[i], cmd);
		if (access(res, X_OK) == 0)
			break ;
		free(res);
		i++;
	}
	if (!path[i])
		res = ft_strdup(cmd);
	free(path);
	return (res);
}

void	argv_init(char *input, t_command *cmd)
{
	int     arg_len;
	int     i;

	if (!is_command(input))
	{
		cmd->argv = ft_calloc(1, sizeof(char *));
		cmd->argv[0] = ft_calloc(1, sizeof(char));
		return ;
	}
	i = 0;
	cmd->d.n_arg = get_n_arg(input);
	cmd->argv = ft_calloc(cmd->d.n_arg, sizeof(char *));
	while (is_command(input))
	{
		while (ft_isspace(input[0]) && input[0])
			input++;
		arg_len = 0;
		while ((!ft_isspace(input[arg_len]) || is_quoted(input, arg_len))
			&& input[arg_len])
			arg_len++;
		cmd->argv[i] = ft_strndup(input, arg_len);
		cmd->argv[i] = remove_quotes(cmd->argv[i]);
		i++;
		input += arg_len;
	}
	return ;
}

int		tokenLen(char *input)
{
	int	res;

	res = 0;
	if (is_metachar(input[0])) 
	{
		res++;
		if (input[0] == '$')
		{
			while (!ft_isspace(input[res]) && !is_metachar(input[res])
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
			while (is_quoted(input, res))
				res++;
			res++;
		}
	}
	else
	{
		while (((input[res] != '<' && input[res] != '>'
			&& !ft_isspace(input[res])) || is_quoted(input, res))
			&& input[res])
			res++;
	}
	return (res);
}

void	tokenize_input(char *input)
{
	int		n_token;
	int		i;

	i = 0;
	n_token = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		i += tokenLen(input + i);
		printf("input + %d = |%s|\n", i, input + i);
		n_token++;
	}
	printf("n_token = %d\n", n_token);
	return ;
}

void	cmd_init(char *input, t_command *cmd)
{
	tokenize_input(input);
	argv_init(input, cmd);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	return ;
}

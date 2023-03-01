/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/01 01:12:38 by vimercie         ###   ########lyon.fr   */
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
	if (!cmd)
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

// void	argv_init_v2(char **tokens, t_command *cmd)
// {
// 	int	i;

// 	while (tokens[i])
// 	{
		
// 		i++;
// 	}
// }

void	argv_init(char *input, t_command *cmd)
{
	int	arg_len;
	int	i;

	if (!is_command(input))
	{
		cmd->argv = ft_calloc(1, sizeof(char *));
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

void	cmd_init(char *input, t_command *cmd)
{
	char	**tokens;

	tokens = tokenize_input(input);
	if (tokens[0] != NULL)
	{
		argv_init(input, cmd);
		cmd->pathname = get_cmd_path(cmd->argv[0]);
	}
	free_tab(tokens);
	return ;
}

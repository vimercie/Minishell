/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/22 11:39:24 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fd_init(char *input, t_command *cmd)
{
	int	i;

	i = 0;
	cmd->fd_in = 0;
	cmd->n_output = output_count(input);
	cmd->fd_out = ft_calloc(cmd->n_output, sizeof(int));
	while (i < cmd->n_output)
	{
		cmd->fd_out[i] = 1;
		i++;
	}
	return ;
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
	cmd->n_arg = get_n_arg(input);
	cmd->argv = ft_calloc(cmd->n_arg, sizeof(char *));
	while (is_command(input))
	{
		while (ft_isspace(input[0]) && input[0])
			input++;
		arg_len = 0;
		while ((!ft_isspace(input[arg_len]) || is_in_quotes(input, arg_len))
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
	fd_init(input, cmd);
	argv_init(input, cmd);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	return ;
}

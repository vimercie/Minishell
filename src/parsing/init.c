/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 02:06:07 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/22 13:55:31 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fd_init(char *input, t_command *cmd)
{
	int	i;

	cmd->n_input = redirect_count(input, '<');
	cmd->n_output = redirect_count(input, '>');
	if (cmd->n_input == 0)
		cmd->n_input = 1;
	if (cmd->n_output == 0)
		cmd->n_output = 1;
	cmd->fd_in = ft_calloc(cmd->n_input, sizeof(int));
	cmd->fd_out = ft_calloc(cmd->n_output, sizeof(int));
	i = 0;
	while (i < cmd->n_input)
	{
		cmd->fd_in[i] = 0;
		i++;
	}
	i = 0;
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
	redirect_fd(input, cmd);
	argv_init(input, cmd);
	cmd->pathname = get_cmd_path(cmd->argv[0]);
	return ;
}

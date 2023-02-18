/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/18 17:14:15 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	prompt_join(char *cmd_line)
{
	char	*buffer;
	char	*tmp;

	while (is_prompt(cmd_line))
	{
		tmp = ft_strjoin(cmd_line, "\n");
		free(cmd_line);
		buffer = readline("> ");
		cmd_line = ft_strjoin(tmp, buffer);
		free(buffer);
		free(tmp);
	}
	return (1);
}

int	parsing(t_data *data, char *input)
{
	prompt_join(input);
	// redirect_fd(input);
	// syntax_cleaner(input);
	// replace_env_v(input);
	cmd_tab_init(input, data);
	return (1);
}

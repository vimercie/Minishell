/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:32:34 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 18:09:30 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*prompt_join(char *input)
{
	char	*res;
	char	*buffer;
	char	*tmp;

	if (!input[0])
		return (input);
	res = ft_strdup(input);
	while (is_prompt(res))
	{
		tmp = ft_strjoin(res, "\n");
		free(res);
		buffer = readline("> ");
		res = ft_strjoin(tmp, buffer);
		free(buffer);
		free(tmp);
	}
	return (res);
}

void	parsing(t_data *data, char *input)
{
	char		*cmd_line;

	cmd_line = prompt_join(input);
	// cmd = redirect_fd(cmd);
	// cmd = syntax_cleaner(cmd);
	// cmd = replace_env_v(cmd);
	cmd_tab_init(cmd_line, data);
	free(cmd_line);
	return ;
}

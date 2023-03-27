/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:58:57 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/27 15:59:10 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main_tester(t_data *data)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	buffer = NULL;
	while (i < data->n_cmd)
	{
		j = 0;
		printf("----- cmd n.%d -----\n", i + 1);
		printf("cmd[%d].pathname = |%s|\n", i, data->cmd[i].pathname);
		while (j < data->cmd[i].d.n_arg || j < 1)
		{
			printf("cmd[%d].argv[%d] = |%s|\n", i, j, data->cmd[i].argv[j]);
			j++;
		}
		printf("cmd[%d].fdIN = |%d|\n", i, data->cmd[i].fd_in);
		printf("cmd[%d].fdOUT = |%d|\n", i, data->cmd[i].fd_out);
		j = 0;
		while (j < data->cmd[i].d.n_redir)
		{
			printf("cmd[%d].files[%d].file_name = |%s|\n", i, j, data->cmd[i].d.files[j].file_name);
			printf("cmd[%d].files[%d].fd = |%d|\n", i, j, data->cmd[i].d.files[j].fd);
			printf("cmd[%d].files[%d].is_outfile = |%d|\n", i, j, data->cmd[i].d.files[j].is_outfile);
			j++;
		}
		if (data->cmd[i].fd_in > 2)
		{
			printf("infile = ");
			buffer = get_next_line(data->cmd[i].fd_in);
			if (!buffer)
				printf("(null)");
			else
			{
				while (buffer)
				{
					printf("%s", buffer);
					free(buffer);
					buffer = get_next_line(data->cmd[i].fd_in);
				}
			}
		}
		printf("\n");
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:11:26 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/22 01:05:22 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_file_name(char *input)
{
	int		start;
	int		len;

	start = 1;
	len = 0;
	if (input[0] == '\0')
		return (NULL);
	while (ft_isspace(input[start]))
		start++;
	while (!ft_isspace(input[start + len]) && input[start + len])
		len++;
	if (len == 0)
		return (NULL);
	return (ft_substr(input, start, len));
}

// char	*trunc_(char *input)
// {
// 	char	*file;
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	if (!input[0])
// 		return (NULL);
// 	res = ft_strdup(input);
// 	res = remove_quotes(res);
// 	while (input[i])
// 	{
// 		if (input[i] == '>' && input)
// 		{
// 			file = get_file_name(input + i);
// 			if (file == NULL)
// 			{
// 				printf("error: no file specified\n");
// 				return (res);
// 			}
// 			free(res);
// 			res = str_trunc(input, i, i + ft_strlen(file) + 1);
// 			free(file);
// 		}
// 		i++;
// 	}
// 	free(input);
// 	return (res);
// }

// void	redirect_fd(t_data *data)
// {
	
// }

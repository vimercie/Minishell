/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:41:34 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/10 15:41:40 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_current_dir(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (!cwd)
		return (0);
	getcwd(cwd, sizeof(char) * 1024);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

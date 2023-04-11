/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:07:06 by mmajani           #+#    #+#             */
/*   Updated: 2023/04/11 14:10:08 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	gotohomedir(void)
{
	char	*homedir;

	homedir = getenv("HOME");
	if (homedir == NULL)
	{
		perror("");
		exit(1);
	}
	else
	{
		if (chdir(homedir) == -1)
		{
			perror("");
			exit(1);
		}
	}
}

// int	goToAbsolutePath(char* path)
// {
// 	if (chdir(path) == -1)
// 	{
// 		perror("");
// 		return (1);
// 	}
// 	return (0);
// }

int	gotorelativepath(char *path)
{
	if (chdir(path) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

void	refresh_pwds_to_env(t_data *data, char *oldpwd)
{
	char	*new;
	char	*tmp;

	tmp = getcwd(NULL, 4096);
	new = calloc(sizeof(char), 32760);
	ft_strlcpy(new, "PWD=", 5);
	ft_strlcat(new, tmp, 4096);
	export(new, data->env);
	export(oldpwd, data->env);
	free(new);
	free(oldpwd);
	if (tmp)
		free(tmp);
}

int	cd(t_data *data)
{
	char	*oldpwd;
	char	*tmp;

	if (data->cmd->d.n_arg > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	oldpwd = calloc(sizeof(char), 32760);
	tmp = getcwd(NULL, 4096);
	ft_strlcpy(oldpwd, "OLDPWD=", 8);
	ft_strlcat(oldpwd, tmp, 4096);
	if (data->cmd->d.n_arg == 2)
		if (gotorelativepath(data->cmd->argv[1]) == 0)
			refresh_pwds_to_env(data, oldpwd);
	if (data->cmd->d.n_arg == 1)
	{
		gotohomedir();
		refresh_pwds_to_env(data, oldpwd);
	}
	if (tmp)
		free(tmp);
	return (0);
}

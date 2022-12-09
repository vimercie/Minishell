/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/09 23:06:33 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../Libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**args;
}				t_command;

// parsing
int		parsing(t_command *cmd);
char	*input_cleaner(char *input);
char	*skip_junk(char *input, char *res, int *i, int *j);

// checking
int		is_junk(char *s);

#endif
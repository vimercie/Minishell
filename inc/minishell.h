/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/19 21:29:42 by vimercie         ###   ########.fr       */
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
	char	*cmd;
	char	**args;
	int		fd_in;
	int		fd_out;
}				t_command;

// parsing
t_command	*parsing(char *cmd);
char		*syntax_cleaner(char *input);
char		*skip_junk(char *input, int *i, int *j);
char		*manage_quote(char *input, int *i, int *j);

// init
t_command	*data_init(char **pipe_split, int n_pipes);
int			count_pipes(char *input);
int			free_tab(char **tab);
int			free_cmd(t_command *cmd);

// checking
int			is_command(char *s);
int			is_junk(char *s);
int			is_quote(char *s);

#endif
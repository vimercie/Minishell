/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/23 18:22:09 by vimercie         ###   ########.fr       */
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
# include <sys/wait.h>
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
	int		has_pipe;
}				t_command;

// parsing
t_command	*parsing(char *cmd);
char		*syntax_cleaner(char *input);
char		*skip_junk(char *input, int *i, int *j);
char		*manage_quote(char *input, int *i, int *j);
char		*remove_quotes(char *s);
char		*gather_full_path(char *path, char *cmd);

// init
t_command	*data_init(char **pipe_split, int n_pipes);
int			count_pipes(char *input);
int			free_tab(char **tab);
int			free_cmd(t_command *cmd);

// checking
int			is_command(char *s);
int			is_junk(char *s);
int			is_quote(char *s);
int			is_in_quotes(char *s, int index);
int			is_ws(char *s);

// exec
int			exec_cmd(t_command *cmd);

//builts-in

char 		*get_current_dir(void);
int 		echo_n(t_command *cmd);
int			export(char *str, char **env);
int			unset_env(char *name, char **env);
int 		cd(int argc, char** argv);

#endif
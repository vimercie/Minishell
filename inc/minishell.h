/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/04 19:32:53 by vimercie         ###   ########.fr       */
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
}				t_command;

typedef struct s_data
{
	t_command	*cmd;
	int			n_cmd;
}				t_data;

int			main_tester(t_command *cmd);

// parsing
t_data		*parsing(char *cmd);
char		*syntax_cleaner(char *input);
char		*skip_ws(char *input, int *i, int *j);
char		*manage_quote(char *input, int *i, int *j);
char		**custom_split(char *s, char c, int n_cmd);

// utils
char		*remove_quotes(char *s);
char		*gather_full_path(char *path, char *cmd);
int			cmd_count(char *s, char c);

// init
t_command	*cmd_tab_init(char **pipe_split, int n_pipes);
int			count_pipes(char *input);
int			free_tab(char **tab);
int			free_cmd(t_command *cmd);

// checking
int			is_prompt(char *s);
int			is_command(char *s);
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
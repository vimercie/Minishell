/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/16 12:23:08 by vimercie         ###   ########.fr       */
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
	char	*pathname;
	char	**argv;
	int		fd_in;
	int		fd_out;
}				t_command;

typedef struct s_data
{
	t_command	*cmd;
	int			n_cmd;
}				t_data;

int		main_tester(t_command *cmd);
int		free_tab(char **tab);
int		free_cmd(t_command *cmd);

// parsing
void	parsing(t_data *data, char *input);
char	*syntax_cleaner(char *input);

// init
void	cmd_tab_init(char *input, t_data *data);
char	**argv_init(char *input);
char	*get_cmd_path(char *cmd);
char	*gather_full_path(char *path, char *cmd);

// utils
char	**custom_split(char *s, char c, int n_cmd);
char	*get_next_word(char *s, char c, int *i);
int		cmd_count(char *s, char c);
int		get_n_arg(char *input);
char	*remove_quotes(char *s);

// redirection
char	*redirect_fd(char *input);

// checking
int		is_meta_char(char c);
int		is_prompt(char *s);
int		is_command(char *s);
int		is_quote(char *s, int index);
int		is_in_quotes(char *s, int index);

// exec
int		exec_cmd(t_command *cmd);

//builts-in
char	*get_current_dir(void);
int 	echo_n(t_command *cmd);
int		export(char *str, char **env);
int		unset_env(char *name, char **env);
int 	cd(int argc, char** argv);

#endif
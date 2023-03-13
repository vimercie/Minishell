/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2023/03/13 18:25:56 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define _XOPEN_SOURCE 700

# include "../Libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env		t_env;
typedef struct	s_data		t_data;
typedef struct	s_redir		t_redir;
typedef struct	s_command	t_command;
typedef	struct	s_cmd_data	t_cmd_data;

typedef struct	s_cmd_data
{
	int			pipefd[2];
	t_redir		*opened_fd;
	int			n_arg;
	int			n_redir;
}				t_cmd_data;

typedef struct	s_redir
{
	int			fd;
	bool		is_outfile;
}				t_redir;

typedef struct	s_command
{
	char		**argv;
	char		*pathname;
	int			fd_in;
	int			fd_out;
	t_cmd_data	d;
}				t_command;

typedef struct	s_env
{
	char		*name;
	char		*value;
	int			val;
	t_env		*next;
}				t_env;

typedef struct	s_data
{
	t_command	*cmd;
	t_env		*env;
	int			n_cmd;
}				t_data;

int		main_tester(t_data *data);
int		free_tab(char **tab);
int		free_cmd(t_command *cmd);

// parsing
int		parsing(char *input, t_data *data);
int		check_syntax(char *input);
char	*handle_env_var(char *input, t_env *env);

// init
void	cmd_init(char **tokens, t_command *cmd, t_env *env);
char	**argv_init(char **tokens, t_env *env);
int		fd_init(t_data *data);

// token handling
char	**tokenize_input(char *input);

// parsing utils
char	**custom_split(char *s, char c, int n_cmd);
char	*get_next_word(char *s, char c, int *i);
int		cmd_count(char *s, char c);

// init utils
char	*get_cmd_path(char *cmd);
char	*gather_full_path(char *path, char *cmd);
char	*remove_quotes(char *s);
int		count_args(char **tokens);

// redirection
int		assign_fd(t_command *cmd);
int 	open_fd(char **tokens, t_command *cmd);
int 	get_fd(char *operator, char *file_name);

// checking
int		is_metachar(char c);
int		is_string_blank(char *s);
int		is_quote(char *s, int index);
int		is_quoted(char *s, int index);

// exec
int		execute(t_data *data, char *buffer);

// env
t_env	*lst_getenv(char **env);
t_env   *lst_name(t_env *lst, char *to_find);
void	lst_free(t_env *lst);
int		print_list(t_env *head);

// builts-in
int		get_current_dir(void);
int 	echo_n(t_command *cmd);
int		export_controller(t_command *cmd, t_env *env);
int 	cd(int argc, char** argv);
int		unset_var(t_command *cmd, t_env *env);
void	exit_gigabash(t_data *data);
int     exit_bash(t_data *data, char *buffer);
void	signal_exit(int signum);

// Signals

int signal_handling(struct sigaction sa, char *buffer);

//builts-in tools

// void 	print_env(char **env);
// int		ft_putenv(char *name, char *value, char **env);
// int 	print_ascii_order_env(char **env);
char	*get_left_part(char *string);
char 	**ft_copyenv(char **env);
int		assign_name_value(t_env *lst_new, char *string);

#endif
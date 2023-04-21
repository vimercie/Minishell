/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
/*   Updated: 2023/04/21 08:18:16 by mmajani          ###   ########lyon.fr   */
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

// variable globale
extern int						g_err_no;

typedef struct s_env			t_env;
typedef struct s_data			t_data;
typedef struct s_command		t_command;
typedef struct s_cmd_data		t_cmd_data;
typedef struct s_file_table		t_file_table;

typedef struct s_env
{
	char		*name;
	char		*value;
	int			val;
	int			index;
	t_env		*next;
}				t_env;

typedef struct s_file_table
{
	char			*file_name;
	int				fd;
	int				is_outfile;
	bool			is_heredoc;
}				t_file_table;

typedef struct s_cmd_data
{
	t_file_table	*files;
	int				pipefd[2];
	int				pid;
	int				n_redir;
	int				n_arg;
	bool			is_builtin;
}				t_cmd_data;

typedef struct s_command
{
	char			**argv;
	char			*pathname;
	int				fd_in;
	int				fd_out;
	t_cmd_data		d;
}				t_command;

typedef struct s_data
{
	t_command			*cmd;
	t_env				*env;
	char				**tab_env;
	int					env_size;
	int					n_cmd;
	struct sigaction	sa;
}						t_data;

int				main_tester(t_data *data);

// parsing
int				parsing(char *input, t_data *data);
int				check_syntax(char *input, char **tokens);
char			*handle_env_var(char *input, bool is_heredoc, t_env *env);
int				pipe_init(t_data *data);

// init
int				cmd_init(char **tokens, t_command *cmd, t_data *data);
char			**argv_init(char **tokens, t_env *env);
char			*get_cmd_path(char *cmd, t_env *env);
t_file_table	*files_init(char **tokens, int n_redir, t_data *data);
int				set_fd(t_data *data);

// token handling
char			**tokenize_input(char *input);
int				token_len(char *input);
int				handle_metachar(char *input);
int				count_tokens(char *input);

// env_var
char			*find_env_var_value(char *to_find, t_env *env);

// redirection
int				find_duplicate(int file_index, t_file_table *files);
int				get_fd(char *operator, char *file_name, t_data *data);

// heredoc
int				heredoc(char *delimiter, t_data *data);

// checking
int				is_builtin(char *str);
int				is_directory(char *path);
int				is_metachar(char c);
int				is_string_blank(char *s);
int				is_pipe(int fd, t_data *data);
int				is_quote(char *s, int index);
int				is_quoted(char *s, int index);

// parsing utils
char			**cmd_pipe_split(char **tokens, int *token_i);
char			*gather_full_path(char *path, char *cmd);
char			*remove_quotes(char *s);

// init utils
int				count_cmd(char **tokens);
int				count_redir(char **tokens);
int				count_token_args(char **tokens);
int				count_args(char **tokens);
int				count_quotes(char	*s);

// file descriptor
int				pipe_init(t_data *data);

// error
int				print_bash_error(char *token, int errnum);
int				print_linux_error(char *token);
int				print_heredoc_warning(char *token);
void			perror_exit(char *str);

// cleaning
void			free_loop(t_data *data);
int				free_tab(char **tab);
int				close_files(t_command *cmd);
int				close_pipes(t_data *data);

// exec
int				execute_commands(t_data *data);
int				built_in_detection(t_command *cmd, t_data *data);
int				wait_child_process(int pid);
int				dup_fd(t_command *cmd);
// env
t_env			*lst_getenv(char **env);
t_env			*lst_name(t_env *lst, char *to_find);
char			**lst_env_to_tab_env(t_env *env);
char			*get_env_name(char *string);
char			*get_env_value(char *string);
char			*get_left_part(char *string);
int				assign_name_value(t_env *lst_new, char *string);
int				print_list(t_env *env);
int				equal_index(char *string);
int				export(char *str, t_env *env);
void			print_sorted_list(t_env *env);
void			index_env(t_env *env);
void			lst_free(t_env *lst);

// builts-in
int				get_current_dir(void);
int				echo_controller(t_command *cmd);
int				export_controller(t_command *cmd, t_env *env);
int				cd(t_data *data);
int				unset_var(t_command *cmd, t_env *env);
int				exit_bash(t_data *data, char *buffer, int val);
void			exit_gigabash(t_data *data);
void			signal_exit(int signum);

// Signals
int				signal_handling(struct sigaction *sa);
int				exec_signal_handling(struct sigaction *sa);
int				child_signal_handling(struct sigaction *sa);
int				heredoc_signal_handling(struct sigaction *sa);
void			prompt_on_new_line(int signum);
int				signal_ignore(t_data *data);

#endif

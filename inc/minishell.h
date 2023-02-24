/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:28:50 by vimercie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/24 16:51:30 by mmajani          ###   ########lyon.fr   */
=======
/*   Updated: 2023/02/24 14:40:42 by vimercie         ###   ########lyon.fr   */
>>>>>>> eda37382dfce5e27adcd0b518b3ef11101ab75ac
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../Libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
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

typedef struct	s_data		t_data;
typedef struct	s_command	t_command;
typedef	struct	s_cmd_data	t_cmd_data;

typedef struct	s_cmd_data
{
	int		pipefd[2];
	int		id;
	int		n_arg;
}				t_cmd_data;

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
}				t_env;

typedef struct	s_data
{
	t_command	*cmd;
	int			n_cmd;
	char		**env;
}				t_data;

int		main_tester(t_data *data);
int		free_tab(char **tab);
int		free_cmd(t_command *cmd);

// parsing
int		parsing(char *input, t_data *data);
int		check_syntax(char *input);
// int		prompt_join(char *cmd_line);

// init
void	cmd_init(char *input, t_command *cmd);
void	argv_init(char *input, t_command *cmd);
void	fd_init(char *input, t_command *cmd);

// parsing utils
char	**custom_split(char *s, char c, int n_cmd);
char	*get_next_word(char *s, char c, int *i);
int		cmd_count(char *s, char c);

// init utils
char	*get_cmd_path(char *cmd);
char	*gather_full_path(char *path, char *cmd);
int		get_n_arg(char *input);
char	*remove_quotes(char *s);

// redirection
int		redirect_fd(char *input, t_command *cmd);
int 	get_fd(char *input);
int		redirect_count(char *input, char c);

// checking
int		is_meta_char(char c);
int		is_prompt(char *s);
int		is_command(char *s);
int		is_quote(char *s, int index);
int		is_in_quotes(char *s, int index);

// exec
int     execute(t_command *cmd, char **envp);

//builts-in
char	*get_current_dir(void);
int 	echo_n(t_command *cmd);
int 	export(char *str, char **envp);
int		unset_env(char *name, char **env);
int 	cd(int argc, char** argv);

//builts-in tools

void 	print_env(char **env);
int		ft_putenv(char *name, char *value, char **env);
int 	print_ascii_order_env(char **env);
char 	**ft_copyenv(char **env);

#endif
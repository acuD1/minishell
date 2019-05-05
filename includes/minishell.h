/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:50:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

# define DEFAULT_TTY "/dev/ttys003"
# define DEFAULT_SHLVL "SHLVL=1"
# define DEFAULT_LA "_=/usr/bin/env"
# define C_R "\x1b[31m"
# define C_G "\x1b[32m"
# define C_Y "\x1b[33m"
# define C_B "\x1b[34m"
# define C_M "\x1b[35m"
# define C_C "\x1b[36m"
# define C_X "\x1b[0m"
# define ENV_DB ((t_db*)(env->content))

typedef struct		s_build
{
	unsigned long	version;
	unsigned long	patch;
	unsigned long	date;
}					t_build;

typedef struct		s_opt
{
	int				v;
	int				h;
	int				d;
}					t_opt;

typedef struct		s_flags
{
	int				stop;
	int				usage;
	int				exit;
}					t_flags;

typedef struct		s_db
{
	char			*symbol;
	char			*value;
}					t_db;

typedef struct		s_core
{
	t_build			build;
	t_opt			opt;
	t_flags			flag;
	t_list			*env;
	pid_t			child_pid;
	char			*logger;
	char			*bin_path;
	int				minishell_pid;
}					t_core;

/*
**	Core
*/

void				signal_handler(void);
void				exec_prompt(t_core *shell);
int					exec_process(t_core *shell, char **tokens);
int					exec_builtins(t_core *shell, char **tokens);

/*
** DB
*/

void				init_shell(t_core *shell);
t_list				*set_env(char **environ);
int					get_opt(int ac, char **av, t_core *shell);
char				**get_envp(t_core *shell);
void				get_path(t_core *shell, char *filename);

/*
**	Misc
*/

void				helper(t_core *shell, char *line, char **tokens);
int					exit_status(t_core *shell, int status);
int					open_logger(t_core *shell);
void				credit(t_core *shell);
void				init_prompt(void);
void				print_opt(t_core *shell);
int					check_filename(char *filename);

/*
**	Tools
*/

void				free_tab(char **tokens);
void				free_list(t_list *env);

/*
**	Dev
*/

void				chdir_closedir(char *dir, DIR *content);

#endif

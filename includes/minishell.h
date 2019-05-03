/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 13:13:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define DEFAULT_TTY "/dev/ttys002"
# define DEFAULT_SHLVL "SHLVL=1"
# define DEFAULT_ENV "_=/usr/bin/env"
# define DEFAULT_PATH "PATH=/usr/bin"
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
	int				fail;
	int				stop;
	int				usage;
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
	char			*logger;
}					t_core;

/*
**	Core
*/

t_list				*set_env(char **environ);
int					get_opt(int ac, char **av, t_core *shell);
void				signal_handler(void);
void				free_list(t_list *env);
void				free_tokens(char **tokens);

/*
**	Misc
*/

void				helper(t_core *shell, char *line, char **tokens);
int					exit_status(t_core *shell);
int					open_logger(t_core *shell);
void				credit(t_core *shell);
void				init_prompt(void);

/*
**	Dev
*/

void				restart_prompt(int s);
void				exec_prompt(t_core *shell);

#endif

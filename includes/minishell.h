/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/13 12:08:58 by arsciand         ###   ########.fr       */
=======
/*   Updated: 2019/04/13 14:25:44 by arsciand         ###   ########.fr       */
>>>>>>> dev
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define FT __func__
# define FL __FILE__
# define LN __LINE__
# define DEFAULT_TTY "/dev/ttys005"
# define C_R "\x1b[31m"
# define C_G "\x1b[32m"
# define C_Y "\x1b[33m"
# define C_B "\x1b[34m"
# define C_M "\x1b[35m"
# define C_C "\x1b[36m"
# define C_X "\x1b[0m"
# define ENV_DB ((t_db*)(env->content))

typedef struct		s_opt
{
	char			*logger;
	int				v;
	int				h;
	int				d;
	int				fail;
	int				stop;
	int				usage;
}					t_opt;

typedef struct		s_build
{
	unsigned long	version;
	unsigned long	number;
	unsigned long	date;
}					t_build;

typedef struct		s_db
{
	char			*symbol;
	char			*value;
}					t_db;

/*
**	Core
*/

t_list				*set_env(char **environ);
int					get_opt(int ac, char **av, t_opt *opt);
void				free_list(t_list *env);
void				signal_handler(void);

/*
**	Misc
*/

void				init_build(t_build *build);
void				helper(t_list *env, t_opt *opt, t_build *build, char *line);
int					exit_status(t_opt *opt, const char *func, char *file,
						int line);
void				credit(t_build *build);
void				init_prompt(void);

/*
**	Dev
*/
#endif

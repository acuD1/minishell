/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/11 14:59:01 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define LOG_TTY "/dev/ttys003"
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
	unsigned long	date;
	char			branch[8];
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
void				free_list(t_list *env);

/*
**	Misc
*/

int					build(int ac, char **av);
void				logger(t_list *env, char **environ);
void				print_env(char **environ, int ttyfd);
void				print_env_db(t_list *env, int ttyfd);

/*
**	Dev
*/


#endif

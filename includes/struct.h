/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:49:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/01 16:57:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# include <limits.h>
# include <stdlib.h>

typedef struct		s_build
{
	uint8_t			release;
	uint8_t			version;
	uint16_t		patch;
	uint32_t		date;
}					t_build;

typedef struct		s_db
{
	char			*symbol;
	char			*value;
}					t_db;

typedef struct		s_pwd
{
	char			current[PATH_MAX];
	char			old[PATH_MAX];
	char			home[PATH_MAX];
	uint8_t			env_oldpwd;
}					t_pwd;

typedef struct		s_core
{
	t_build			build;
	t_db			db;
	t_pwd			pwd;
	t_list			*env;
	t_list			*tmp_env;
	t_list			*var;
	char			**environ;
	char			*bin;
	pid_t			child_pid;
	int32_t			logger_fd;
	int32_t			minishell_pid;
	int8_t			status;
	uint8_t			exit;
	uint8_t			opt;
	uint8_t			builtin;
	uint8_t			default_env;
	u_int8_t		env_mode;
}					t_core;

#endif

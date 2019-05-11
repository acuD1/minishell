/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:49:40 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 14:45:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# include "stdlib.h"

typedef struct		s_build
{
	uint8_t			version;
	uint8_t			patch;
	uint32_t		date;
}					t_build;

typedef struct		s_db
{
	char			*symbol;
	char			*value;
}					t_db;

typedef struct		s_core
{
	t_build			build;
	t_db			db;
	t_list			*env;
	t_list			*var;
	char			*bin;
	pid_t			child_pid;
	int32_t			logger_fd;
	int32_t			minishell_pid;
	int8_t			status;
	uint8_t			exit;
	uint8_t			opt;
}					t_core;

#endif

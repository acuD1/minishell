/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:15:19 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/12 12:43:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define SUCCESS		0
# define FAILURE		-1
# define FALSE			0
# define TRUE			1
# define BIN_ERROR		0x001
# define PATH_ERROR		0x002
# define FORK_ERROR		0x004
# define PERM_ERROR		0x008
# define EXEC_ERROR		0x010
# define OPT_HELP		0x001
# define OPT_DEBG		0x002
# define OPT_VERS		0x004
# define FREE_1			1
# define FREE_2			2
# define FREE_ALL		3
# define LOGGER_TTY		"/dev/ttys003"
# define DEFAULT_SHLVL	"SHLVL=1"
# define DEFAULT_LA		"_=/usr/bin/env"
# define C_R			"\x1b[31m"
# define C_G			"\x1b[32m"
# define C_Y			"\x1b[33m"
# define C_B			"\x1b[34m"
# define C_M			"\x1b[35m"
# define C_C			"\x1b[36m"
# define C_X			"\x1b[0m"

#endif

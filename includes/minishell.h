/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/07 13:22:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

extern char **environ;

typedef struct		s_build
{
	unsigned long	version;
	unsigned long	date;
	char			branch[8];
}					t_build;

typedef struct		s_db
{
	char			*symbol;
	char			*path;
}					t_db;

/*
**	Core
*/

/*
**	Misc
*/

void			build(void);

#endif

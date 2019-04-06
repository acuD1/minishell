/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/06 16:35:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

#include <stdio.h>

typedef struct		s_build
{
	unsigned long	version;
	unsigned long	date;
	char			branch[8];
}					t_build;

/*
**	Core
*/

/*
**	Misc
*/

void			build(void);

#endif

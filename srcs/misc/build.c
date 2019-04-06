/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:46:59 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/06 15:53:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define XSTR(x) #x
#define STR(x) XSTR(x)

void	build(void)
{
	t_build	build;

	ft_bzero(&build, sizeof(t_build));
	build.version = BUILD + 1;
	build.date = DATE;
	ft_strcpy(build.branch, STR(BRANCH));
	ft_mprintf(1, "minishell v.%d_%d_%s\n",
		build.version, build.date, build.branch);
}

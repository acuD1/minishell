/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 13:42:43 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **environ, int ttyfd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUF FOR ENV ->", ttyfd);
	if (!(environ[i]))
		ft_mprintf(ttyfd, "%sEMPTY%s\n", C_R, C_X);
	while (environ[i])
	{
		ft_mprintf(ttyfd, "%sENV[%s%d%s]%s%s\n",
			C_Y, C_G, i, C_Y, C_X, environ[i]);
		i++;
	}
}

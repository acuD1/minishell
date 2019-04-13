/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/13 09:28:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **environ, int fd)
{
	int		i;

	i = 0;
	ft_putendl_fd("DEBUF FOR ENV ->", fd);
	if (!(environ[i]))
		ft_mprintf(fd, "%sEMPTY%s\n", C_R, C_X);
	while (environ[i])
	{
		ft_mprintf(fd, "%sENV[%s%d%s]%s%s\n",
			C_Y, C_G, i, C_Y, C_X, environ[i]);
		i++;
	}
}

int		open_logger(t_opt *opt)
{
	int		fd;

	if ((fd = open(opt->logger,
		O_WRONLY | O_APPEND | O_CREAT | O_NOFOLLOW, 0600)) == -1)
	{
		opt->stop = 1;
		ft_mprintf(1, "%sFailed open %s for debug !%s\n",
			C_R, opt->logger, C_X);
		return (0);
	}
	return (fd);
}

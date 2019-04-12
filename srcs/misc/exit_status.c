/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:59:38 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/12 15:05:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_status(t_opt *opt, const char *func, char *file, int line)
{
	int		ttyfd;

	if (!opt->usage)
	{
		if ((ttyfd = open(opt->logger, O_WRONLY | O_APPEND | O_CREAT
			| O_NOFOLLOW, 0600)) == -1 && !opt->stop)
			ft_mprintf(STDERR_FILENO, "%sFailed open %s for debug !%s\n",
				C_R, opt->logger, C_X);
	}
	free(opt->logger);
	if (opt->fail)
	{
		if (opt->d)
			ft_mprintf(ttyfd, "\n%sEXIT_FAILURE%s %s %s %d",
				C_R, C_X, file, func, line);
		return (EXIT_FAILURE);
	}
	if (opt->d)
		ft_mprintf(ttyfd, "\n%sEXIT_SUCCESS%s", C_G, C_X);
	return (EXIT_SUCCESS);
}

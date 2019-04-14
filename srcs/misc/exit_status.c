/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:59:38 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/14 12:53:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_status(t_opt *opt, const char *func, char *file, int line)
{
	int		fd;

	if (!opt->usage)
		fd = open_logger(opt);
	free(opt->logger);
	if (opt->fail)
	{
		if (opt->d)
			ft_mprintf(fd, "\n%sEXIT_FAILURE%s %s %s %d",
				C_R, C_X, file, func, line);
		return (EXIT_FAILURE);
	}
	if (opt->d)
		ft_mprintf(fd, "\n%sEXIT_SUCCESS%s", C_G, C_X);
	ft_mprintf(STDOUT_FILENO, "\n\n%sExiting...%s\n", C_Y, C_X);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:59:38 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 10:03:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_status(t_core *shell, int status)
{
	int		fd;

	if (!shell->flag.usage)
		fd = open_logger(shell);
	free(shell->logger);
	if (status)
	{
		if (shell->opt.d)
			ft_mprintf(fd, "\n%sEXIT_FAILURE%s", C_R, C_X);
		return (EXIT_FAILURE);
	}
	if (shell->opt.d)
		ft_mprintf(fd, "\n%sEXIT_SUCCESS%s", C_G, C_X);
	if (!shell->flag.exit)
		write(STDOUT_FILENO, "\n", 1);
	ft_mprintf(STDOUT_FILENO, "\n%sExiting...%s\n", C_Y, C_X);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:59:38 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 16:17:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int8_t		exit_handler(t_core *shell, int status)
{
	free_core(shell);
	if (status)
	{
		if (shell->opt & OPT_DEBG && shell->logger_fd != -1)
			ft_mprintf(shell->logger_fd, "\n%sEXIT_FAILURE%s", C_R, C_X);
		return (EXIT_FAILURE);
	}
	if (shell->opt & OPT_DEBG && shell->logger_fd != -1)
		ft_mprintf(shell->logger_fd, "\n%sEXIT_SUCCESS%s", C_G, C_X);
	if (shell->exit == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_mprintf(STDOUT_FILENO, "\n%sExiting...%s\n", C_Y, C_X);
	return (EXIT_SUCCESS);
}

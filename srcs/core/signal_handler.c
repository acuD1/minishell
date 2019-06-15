/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:20:08 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/15 15:32:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	restart_prompt(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	init_prompt();
}

static void	do_nothing(int sig)
{
	(void)sig;
	ft_mprintf(STDERR_FILENO, "\nSIGTSTP not supported\n");
	init_prompt();
}

void		signal_handler(void)
{
	signal(SIGINT, restart_prompt);
	signal(SIGTSTP, do_nothing);
}

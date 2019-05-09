/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:20:08 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 16:17:06 by arsciand         ###   ########.fr       */
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

void		signal_handler(void)
{
	signal(SIGINT, restart_prompt);
}

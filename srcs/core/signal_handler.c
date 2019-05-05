/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:20:08 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 10:37:00 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restart_prompt(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n", 1);
	init_prompt();
}

void		signal_handler(void)
{
	if (signal(SIGINT, restart_prompt) == SIG_ERR)
		ft_putendl("?");
}

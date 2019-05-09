/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:13:45 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:14:38 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>

void	init_shell(t_core *shell)
{
	ft_bzero(&shell->opt, sizeof(shell->opt));
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->logger_fd = -1;
	shell->env = NULL;
	shell->bin = NULL;
	shell->minishell_pid = getpid();
	shell->child_pid = 0;
	shell->status = 1;
	shell->exit = 0;
}

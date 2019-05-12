/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:13:45 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/12 16:05:33 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>

void	init_shell(t_core *shell)
{
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->db.symbol = NULL;
	shell->db.value = NULL;
	shell->logger_fd = -1;
	shell->env = NULL;
	shell->tmp_env = NULL;
	shell->var = NULL;
	shell->bin = NULL;
	shell->minishell_pid = getpid();
	shell->child_pid = 0;
	shell->status = 1;
	shell->exit = 0;
	shell->opt = 0;
	shell->default_env = 0;
	shell->env_mode = 0;
}

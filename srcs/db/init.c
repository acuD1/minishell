/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:13:45 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 10:14:00 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_core *shell)
{
	ft_bzero(&shell->opt, sizeof(t_opt));
	ft_bzero(&shell->flag, sizeof(t_flags));
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->env = NULL;
	shell->logger = NULL;
	shell->bin_path = NULL;
	shell->minishell_pid = getpid();
	shell->child_pid = 0;
}

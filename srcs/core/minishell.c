/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 13:01:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>

static void	init_shell(t_core *shell)
{
	ft_bzero(&shell->opt, sizeof(t_opt));
	ft_bzero(&shell->flag, sizeof(t_flags));
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->env = NULL;
	shell->logger = NULL;
}

int			main(int ac, char **av, char **environ)
{
	t_core shell;

	init_shell(&shell);
	if (!(get_opt(ac, av, &shell)))
		return (exit_status(&shell));
	if (!(shell.env = set_env(environ)))
	{
		shell.flag.fail = 1;
		helper(&shell, NULL, NULL);
		return (exit_status(&shell));
	}
	helper(&shell, NULL, NULL);
	signal_handler();
	if (!shell.opt.v && !shell.opt.h)
		exec_prompt(&shell);
	free_list(shell.env);
	return (exit_status(&shell));
}

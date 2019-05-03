/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 15:11:12 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_core *shell)
{
	ft_bzero(&shell->opt, sizeof(t_opt));
	ft_bzero(&shell->flag, sizeof(t_flags));
	shell->build.version = BUILDV;
	shell->build.patch = BUILDP + 1;
	shell->build.date = DATE;
	shell->env = NULL;
	shell->logger = NULL;
	shell->minishell_pid = getpid();
	shell->child_pid = 0;
}

int			main(int ac, char **av, char **environ)
{
	t_core shell;

	init_shell(&shell);
	if (!(get_opt(ac, av, &shell)) || !(shell.env = set_env(environ)))
		return (exit_status(&shell, 1));
	print_opt(&shell);
	signal_handler();
	// LOGGER
	helper(&shell, NULL, NULL);
	// LOGGER
	exec_prompt(&shell);
	free_list(shell.env);
	return (exit_status(&shell, 0));
}

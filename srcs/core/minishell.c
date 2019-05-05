/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:49:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int ac, char **av, char **environ)
{
	t_core	shell;

	init_shell(&shell);
	if (!(get_opt(ac, av, &shell)) || !(shell.env = set_env(environ)))
		return (exit_status(&shell, EXIT_FAILURE));
	print_opt(&shell);
	signal_handler();
	// LOGGER
	helper(&shell, NULL, NULL);
	// LOGGER
	exec_prompt(&shell);
	free_list(shell.env);
	return (exit_status(&shell, EXIT_SUCCESS));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/15 13:00:22 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	t_core	shell;

	init_shell(&shell, environ);
	if ((get_opt(ac, av, &shell) || set_env(&shell, shell.environ)) != SUCCESS)
		return (exit_handler(&shell, EXIT_FAILURE));
	print_opt(&shell);
	signal_handler();
	logger(&shell, NULL, NULL);
	exec_prompt(&shell);
	return (exit_handler(&shell, EXIT_SUCCESS));
}

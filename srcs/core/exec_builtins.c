/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 14:41:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

static uint8_t		builtins_parser(char *tokens)
{
	uint8_t builtin;

	builtin = '\0';
	if (ft_strequ(tokens, "exit") == TRUE)
		builtin |= EXIT_BUILTIN;
	else if (ft_strequ(tokens, "cd") == TRUE)
		builtin |= CD_BUILTIN;
	else if (ft_strequ(tokens, "echo") == TRUE)
		builtin |= ECHO_BUILTIN;
	else if (ft_strequ(tokens, "env") == TRUE)
		builtin |= ENV_BUILTIN;
	else if (ft_strequ(tokens, "unsetenv"))
		builtin |= USETE_BUILTIN;
	else
		builtin |= NO_BUILTIN;
	return (builtin);
}

int8_t				exec_builtins(t_core *shell, char **tokens)
{
	uint8_t builtin;

	builtin = builtins_parser(tokens[0]);
	logger(shell, NULL, tokens);
	if (builtin & NO_BUILTIN)
		return (FAILURE);
	if (builtin & EXIT_BUILTIN)
		shell->exit = TRUE;
	if (builtin & CD_BUILTIN)
		cd_builtin(shell, tokens);
	if (builtin & ECHO_BUILTIN)
		echo_builtin(tokens);
	if (builtin & USETE_BUILTIN
		&& unsetenv_builtin(&shell->env, tokens) != SUCCESS)
		ft_mprintf(STDERR_FILENO,
			"unsetenv: %s: symbol not found in environement\n", tokens[1]);
	if (builtin & ENV_BUILTIN)
	{
		shell->env_mode = 1;
		env_builtin(shell, tokens);
	}
	return (SUCCESS);
}

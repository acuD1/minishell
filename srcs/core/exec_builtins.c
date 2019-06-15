/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/15 13:19:54 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

void	builtins_parser(t_core *shell, char *tokens)
{
	if (ft_strequ(tokens, "exit") == TRUE)
		shell->builtin |= EXIT_BUILTIN;
	else if (ft_strequ(tokens, "cd") == TRUE)
		shell->builtin |= CD_BUILTIN;
	else if (ft_strequ(tokens, "echo") == TRUE)
		shell->builtin |= ECHO_BUILTIN;
	else if (ft_strequ(tokens, "env") == TRUE)
		shell->builtin |= ENV_BUILTIN;
	else if (ft_strequ(tokens, "unsetenv") == TRUE)
		shell->builtin |= USETE_BUILTIN;
	else if (ft_strequ(tokens, "setenv") == TRUE)
		shell->builtin |= SETE_BUILTIN;
	else if (ft_strequ(tokens, "pwd") == TRUE)
		shell->builtin |= PWD_BUILTIN;
	else
		shell->builtin |= NO_BUILTIN;
}

static void	exec_env_modifier(t_core *shell, char **tokens)
{
	if (shell->builtin & USETE_BUILTIN
		&& unsetenv_builtin(&shell->env, tokens) != SUCCESS)
		ft_mprintf(STDERR_FILENO,
			"unsetenv: %s: symbol not found in environement\n", tokens[1]);
	if (shell->builtin & SETE_BUILTIN
		&& setenv_builtin(shell, &shell->env, tokens) != SUCCESS)
		ft_mprintf(STDERR_FILENO,
			"setenv: %s: symbol already exist, set nonzero to overwrite\n",
			tokens[1]);
	if (shell->builtin & ENV_BUILTIN)
	{
		shell->env_mode = 1;
		env_builtin(shell, tokens);
	}
}

int8_t		exec_builtins(t_core *shell, char **tokens)
{
	builtins_parser(shell, tokens[0]);
	logger(shell, NULL, tokens);
	if (shell->builtin & NO_BUILTIN)
		return (FAILURE);
	if (shell->builtin & EXIT_BUILTIN)
		exit_builtin(shell, tokens);
	if (shell->builtin & CD_BUILTIN)
		cd_builtin(shell, tokens);
	if (shell->builtin & ECHO_BUILTIN)
		echo_builtin(tokens);
	if (shell->builtin & PWD_BUILTIN)
		pwd_builtin();
	exec_env_modifier(shell, tokens);
	return (SUCCESS);
}

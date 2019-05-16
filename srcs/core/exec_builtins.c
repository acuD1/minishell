/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 11:08:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

int8_t		exec_builtins(t_core *shell, char **tokens)
{
	logger(shell, NULL, tokens);
	if (ft_strequ(tokens[0], "exit") == TRUE)
	{
		shell->exit = TRUE;
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "cd") == TRUE)
	{
		cd_builtin(shell, tokens);
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "echo") == TRUE)
	{
		echo_builtin(tokens);
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "env") == TRUE)
	{
		shell->env_mode = 1;
		env_builtin(shell, tokens);
		return (SUCCESS);
	}
	return (FAILURE);
}

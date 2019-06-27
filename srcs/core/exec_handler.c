/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 10:31:47 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 10:32:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void exec_handler_bin_error(t_core *shell, char **tokens)
{
	struct stat stat;

	lstat(tokens[0], &stat);
	if (S_ISDIR(stat.st_mode) && shell->exp == 1)
	{
		shell->exp = 0;
		ft_mprintf(STDERR_FILENO, "minishell: %s: is a directory\n",
			tokens[0]);
	}
	else if (shell->env_mode)
		ft_mprintf(STDERR_FILENO, "env: %s: No such file or directory\n",
			tokens[0]);
	else
		ft_mprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			tokens[0]);
}

static void	exec_handler_perm_error(char **tokens)
{
	if (access(tokens[0], F_OK) == -1)
		ft_mprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", tokens[0]);
	else
		ft_mprintf(STDERR_FILENO, "minishell: %s: Permission denied\n",
			tokens[0]);
}

void	exec_handler(t_core *shell, char **tokens, uint8_t handler)
{
	if (handler & BIN_ERROR)
		return (exec_handler_bin_error(shell, tokens));
	if (handler & PERM_ERROR)
		return (exec_handler_perm_error(tokens));
	if (handler & FORK_ERROR)
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s", C_R, C_X);
	if (handler & EXEC_ERROR)
	{
		ft_mprintf(STDERR_FILENO, "%sExecve failed !\n%s", C_R, C_X);
		exit(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:20:02 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:42:56 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_handler(t_core *shell, char **tokens, char **envp)
{
	if (shell->bin_path == NULL)
	{
		ft_mprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			tokens[0]);
		return (0);
	}
	if (access(shell->bin_path, X_OK) == -1)
	{
		ft_mprintf(STDERR_FILENO, "minishell: permission denied: %s\n",
			tokens[0]);
		return (0);
	}
	if (execve(shell->bin_path, tokens, envp) < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sExecve failed ! PATH may be incorrect\n%s",
			C_R, C_X);
		return (0);
	}
	return (1);
}

int			exec_process(t_core *shell, char **tokens)
{
	char	**envp;
	int		status;

	if (tokens[0] == NULL)
		return (0);
	get_path(shell, tokens[0]);
	if (exec_builtins(shell, tokens))
		return (1);
	envp = get_envp(shell);
	if ((shell->child_pid = fork()) < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s",
			C_R, C_X);
		exit(1);
	}
	if (shell->child_pid == 0)
	{
		if (!(exec_handler(shell, tokens, envp)))
			exit(1);
	}
	else
		waitpid(shell->child_pid, &status, WUNTRACED);
	ft_strdel(&shell->bin_path);
	free_tab(envp);
	return (1);
}

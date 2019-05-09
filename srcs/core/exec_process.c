/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:11:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:20:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	exec_handler(char **tokens, unsigned int handler)
{
	if (handler & BIN_CHECK)
	{
		ft_mprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			tokens[0]);
		return ;
	}
	if (handler & PID_CHECK)
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s", C_R, C_X);
	if (handler & PERM_CHECK)
		ft_mprintf(STDERR_FILENO, "minishell: permission denied: %s\n",
		tokens[0]);
	if (handler & EXEC_CHECK)
		ft_mprintf(STDERR_FILENO,
			"%sExecve failed ! PATH may be incorrect\n%s", C_R, C_X);
	exit(1);
}

void		exec_process(t_core *shell, char **tokens)
{
	char	**envp;
	int		status;

	envp = NULL;
	if (tokens[0] == NULL)
		return ;
	shell->bin = get_bin(shell, tokens[0]);
	if (shell->bin == NULL)
		return (exec_handler(tokens, BIN_CHECK));
	envp = get_envp(shell);
	if ((shell->child_pid = fork()) < 0)
		return (exec_handler(tokens, PID_CHECK));
	if (access(shell->bin, X_OK) == FAILURE)
		return (exec_handler(tokens, PERM_CHECK));
	if (shell->child_pid == 0 && execve(shell->bin, tokens, envp) < 0)
		return (exec_handler(tokens, EXEC_CHECK));
	else
		waitpid(shell->child_pid, &status, WUNTRACED);
	free_tab(envp);
}

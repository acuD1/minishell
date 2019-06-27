/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:11:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 11:59:20 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char	**exp_handler(t_core *shell, char **tokens)
{
	if (!(tokens[0][0] == '$') || !(tokens[0][1]))
		return (tokens);
	if (exp_shifter(shell, tokens) == SUCCESS)
	{
		shell->exp = 1;
		return (tokens);
	}
	return (NULL);
}

static void	waitpid_status_handler(t_core *shell)
{
	if (WIFSIGNALED(shell->status))
		ft_mprintf(STDERR_FILENO,
			"Process killed by : SIG%d\n", WTERMSIG(shell->status));
}

void		exec_process(t_core *shell, t_list *env, char **tokens)
{
	char	**envp;

	envp = NULL;
	if (exp_handler(shell, tokens) == NULL)
		return ;
	shell->bin = get_bin(shell, env, tokens[0]);
	if (shell->bin == NULL)
		return (exec_handler(shell, tokens, BIN_ERROR));
	if (access(shell->bin, X_OK) == FAILURE)
		return (exec_handler(shell, tokens, PERM_ERROR));
	if ((shell->child_pid = fork()) < 0)
		return (exec_handler(shell, tokens, FORK_ERROR));
	envp = get_envp(shell, env);
	if (shell->child_pid == 0 && execve(shell->bin, tokens, envp) < 0)
	{
		ft_free_tab(&envp);
		return (exec_handler(shell, tokens, EXEC_ERROR));
	}
	else
	{
		waitpid(shell->child_pid, &shell->status, WCONTINUED);
		waitpid_status_handler(shell);
	}
	ft_free_tab(&envp);
}

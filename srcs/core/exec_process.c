/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:20:02 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/08 18:02:12 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	exec_handler(t_core *shell, char **tokens, char **envp)
{
	if (shell->flag.no_path || shell->bin_path == NULL)
	{
		ft_mprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			tokens[0]);
		return (FAILURE);
	}
	if (shell->child_pid < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s", C_R, C_X);
		return (FAILURE);
	}
	if (access(shell->bin_path, X_OK) == -1)
	{
		ft_mprintf(STDERR_FILENO, "minishell: permission denied: %s\n",
			tokens[0]);
		return (FAILURE);
	}
	if (execve(shell->bin_path, tokens, envp) < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sExecve failed ! PATH may be incorrect\n%s",
			C_R, C_X);
		return (FAILURE);
	}
	return (SUCCESS);
}

void		exec_process(t_core *shell, char **tokens)
{
	char	**envp;
	int		status;

	envp = NULL;
	if (tokens[0] == NULL)
		return ;
	if (get_path(shell, tokens[0]) != SUCCESS
			&& exec_handler(shell, tokens, envp))
		return ;
	envp = get_envp(shell);
	if ((shell->child_pid = fork()) < 0
		&& exec_handler(shell, tokens, envp) != SUCCESS)
		exit(1);
	if (shell->child_pid == 0
		&& exec_handler(shell, tokens, envp) != SUCCESS)
		exit(1);
	else
		waitpid(shell->child_pid, &status, WUNTRACED);
	free_tab(envp);
}

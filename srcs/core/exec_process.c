/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:11:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/26 17:39:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

/*
** TEST
*/

static int8_t	shift_exp_tokens(t_list *env, t_list *var, char *tokens, char *tmp)
{
	while (var)
	{
		if (ft_strequ(((t_db*)(var->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(var->content))->value);
			return (SUCCESS);
		}
		var = var->next;
	}
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(env->content))->value);
			return (SUCCESS);
		}
		env = env->next;
	}
	ft_strdel(&tmp);
	return (FAILURE);

}

static int8_t	exp_shifter(t_core *shell, char *tokens)
{
	t_list	*env;
	t_list	*var;
	char	*tmp;

	env = shell->env;
	var = shell->var;
	tmp = ft_strsub(tokens, 1, ft_strlen(tokens));
	return (shift_exp_tokens(env, var, tokens, tmp));
}

/*
**
*/

static void	exec_handler(t_core *shell, char **tokens, uint8_t handler)
{
	if (handler & BIN_ERROR)
	{
		if (shell->env_mode)
			ft_mprintf(STDERR_FILENO, "env: %s: No such file or directory\n",
				tokens[0]);
		else
			ft_mprintf(STDERR_FILENO, "minishell: %s: command not found\n",
				tokens[0]);
	}
	if (handler & PERM_ERROR)
	{
		if (access(tokens[0], F_OK) == -1)
			ft_mprintf(STDERR_FILENO,
				"minishell: %s: No such file or directory\n", tokens[0]);
		else
			ft_mprintf(STDERR_FILENO, "minishell: %s: Permission denied\n",
				tokens[0]);
	}
	if (handler & FORK_ERROR)
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s", C_R, C_X);
	if (handler & EXEC_ERROR)
	{
		ft_mprintf(STDERR_FILENO, "%sExecve failed !\n%s", C_R, C_X);
		exit(1);
	}
}

static char	*exp_handler(t_core *shell, char **tokens)
{
/*	t_list	*var;
	t_list	*env;
	char	*tmp;

	var = shell->var;
	env = shell->env;*/
	if (!(tokens[0][0] == '$') || !(tokens[0][1]))
		return (tokens[0]);
	ft_mprintf(STDOUT_FILENO, "?\n");
	/*tmp = ft_strsub(tokens[0], 1, ft_strlen(tokens[0]));
	while (var)
	{
		if (ft_strequ(((t_db*)(var->content))->symbol, tmp))
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens[0]);
			tokens[0] = ft_strdup(((t_db*)(var->content))->value);
			return (tokens[0]);
		}
		var = var->next;
	}
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, tmp))
		{
			ft_strdel(&tmp);
			ft_strdel(&tokens[0]);
			tokens[0] = ft_strdup(((t_db*)(env->content))->value);
			return (tokens[0]);
		}
		env = env->next;
	}
	ft_strdel(&tmp);*/
	if (exp_shifter(shell, tokens[0]) == SUCCESS)
	{
		ft_mprintf(STDOUT_FILENO, "Alo?\n");
		return (tokens[0]);
	}
	return (NULL);
}

static void waitpid_status_handler(int status)
{
	if (WIFSIGNALED(status))
		ft_mprintf(STDERR_FILENO,
			"Process killed by : SIG%d\n", WTERMSIG(status));
}

void		exec_process(t_core *shell, t_list *env, char **tokens)
{
	char	**envp;
	int		status;

	envp = NULL;
	if (exp_handler(shell, &tokens[0]) == NULL)
		return ;
	ft_mprintf(STDOUT_FILENO, "tokens ? = |%s|\n", tokens[0]);
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
		waitpid(shell->child_pid, &status, WCONTINUED);
		waitpid_status_handler(status);
	}
	ft_free_tab(&envp);
}

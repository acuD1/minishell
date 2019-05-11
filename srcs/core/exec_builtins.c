/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 15:43:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

static void	get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			chdir(((t_db*)(env->content))->value);
		env = env->next;
	}
}

static void	cd_builtin(t_core *shell, char **tokens)
{
	DIR	*content;

	content = NULL;
	if (tokens[1] == NULL)
		get_env_home(shell->env);
	else
	{
		if (access(tokens[1], F_OK) == -1)
		{
			ft_mprintf(STDERR_FILENO,
				"minishell: cd: %s: No such file or directory\n", tokens[1]);
			return ;
		}
		if (!(content = opendir(tokens[1])))
		{
			ft_mprintf(STDERR_FILENO, "minishell: cd: %s: Permission denied\n",
				tokens[1]);
			return ;
		}
		chdir(tokens[1]);
		closedir(content);
	}
}

int8_t		exec_builtins(t_core *shell, char **tokens)
{
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
	return (FAILURE);
}

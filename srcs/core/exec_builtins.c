/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:39:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <dirent.h>

static void		get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			chdir(((t_db*)(env->content))->value);
		env = env->next;
	}
}

static int8_t	cd_builtin(t_core *shell, char **tokens)
{
	DIR	*content;

	content = NULL;
	if (tokens[1] == NULL)
		get_env_home(shell->env);
	else
	{
		if (!(content = opendir(tokens[1])))
		{
			ft_mprintf(STDERR_FILENO, "cd: permission denied: %s\n",
				tokens[1]);
			return (FAILURE);
		}
		chdir(tokens[1]);
		closedir(content);
	}
	return (SUCCESS);
}

int8_t			exec_builtins(t_core *shell, char **tokens)
{
	if (ft_strequ(tokens[0], "exit") == TRUE)
	{
		shell->exit = TRUE;
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "cd") == TRUE)
		return (cd_builtin(shell, tokens));
	else
		return (FAILURE);
}

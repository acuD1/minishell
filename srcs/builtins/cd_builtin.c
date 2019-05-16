/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:52:12 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 11:08:10 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <unistd.h>

static void	get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			chdir(((t_db*)(env->content))->value);
		env = env->next;
	}
}

void		cd_builtin(t_core *shell, char **tokens)
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

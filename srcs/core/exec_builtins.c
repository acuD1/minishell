/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:41:00 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env_home(t_list *env)
{
	while (env)
	{
		if (ft_strequ(ENV_DB->symbol, "HOME"))
			chdir(ENV_DB->value);
		env = env->next;
	}
}

int		cd_builtin(t_core *shell, char **tokens)
{
	DIR		*content;

	if (shell->bin_path == NULL)
	{
		if (check_filename(tokens[0]))
			return (1);
		if (!(content = opendir(tokens[0])))
			return (0);
		chdir_closedir(tokens[0], content);
		return (1);
	}
	if (ft_strequ(tokens[0], "cd"))
	{
		if (!tokens[1])
			get_env_home(shell->env);
		else
		{
			if (!(content = opendir(tokens[1])))
				ft_mprintf(STDERR_FILENO, "cd: permission denied: %s\n",
					tokens[1]);
			chdir_closedir(tokens[1], content);
		}
		return (1);
	}
	return (0);
}

int		exec_builtins(t_core *shell, char **tokens)
{
	if (ft_strequ(tokens[0], "exit"))
	{
		free(shell->bin_path);
		shell->flag.exit = 1;
		return (1);
	}
	if (cd_builtin(shell, tokens))
		return (1);
	return (0);
}

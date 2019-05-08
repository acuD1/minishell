/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:15:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/08 15:59:10 by arsciand         ###   ########.fr       */
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

	if (!tokens[1])
		get_env_home(shell->env);
	else
	{
		if (!(content = opendir(tokens[1])))
		{
			ft_mprintf(STDERR_FILENO, "cd: permission denied: %s\n",
				tokens[1]);
			return (FAILURE);
		}
		chdir_closedir(tokens[1], content);
	}
	printf ("SUCCES\n");
	return (SUCCESS);
}

int8_t	exec_builtins(t_core *shell, char **tokens)
{
	if (ft_strequ(tokens[0], "exit"))
	{
		shell->flag.exit = 1;
		return (SUCCESS);
	}
	if (ft_strequ(tokens[0], "cd"))
		return (cd_builtin(shell, tokens));
	else
		return (FAILURE);
}

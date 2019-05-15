/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:27:03 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/15 14:00:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envp(t_core *shell, t_list *env)
{
	char	**envp;
	size_t	i;

	i = 0;
	env = NULL;
	if (shell->default_env == TRUE)
		set_default_env(shell, env);
	else
	{
		if (shell->env_mode == TRUE)
			env = shell->tmp_env;
		else
			env = shell->env;
	}
	if (!(envp = ft_memalloc(sizeof(envp) * ((ft_lstlen(env)) + 1))))
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoinf(ft_strjoin(((t_db*)(env->content))->symbol, "="),
						((t_db*)(env->content))->value, 1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

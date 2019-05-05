/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:27:03 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:58:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_envp(t_core *shell)
{
	t_list	*env;
	char	**envp;
	int		i;

	i = 0;
	env = shell->env;
	if (!(envp = ft_memalloc(sizeof(envp) * ((ft_lstlen(env)) + 1))))
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoinf(ft_strjoin(ENV_DB->symbol, "="),
						ENV_DB->value, 1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

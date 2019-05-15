/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/15 17:40:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

void	define_env_list(t_core *shell, t_list *env)
{
	if (shell->env_mode == TRUE)
		shell->tmp_env = env;
	else
		shell->env = env;
}

int8_t	set_default_env(t_core *shell, t_list *env)
{
	t_db	env_db;
	char	*default_environ[4];
	char	pwd[PATH_MAX];
	size_t	i;

	i = 0;
	env_db = shell->db;
	*default_environ = NULL;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		default_environ[0] = ft_strjoin("PWD=", pwd);
	else
		return (FAILURE);
	default_environ[1] = DEFAULT_SHLVL;
	default_environ[2] = DEFAULT_LA;
	default_environ[3] = NULL;
	while (default_environ[i])
	{
		ft_lstpushback(&env,
			ft_lstnew(fetch_db(&env_db, default_environ[i]), sizeof(t_db)));
		i++;
	}
	define_env_list(shell, env);
	ft_strdel(&default_environ[0]);
	return (SUCCESS);
}

int8_t			set_env(t_core *shell, char **environ)
{
	t_db	env_db;
	t_list	*env;
	size_t	i;

	i = 0;
	env = NULL;
	env_db = shell->db;
	if (environ == NULL || *environ == NULL)
		return (set_default_env(shell, env));
	while (environ[i])
	{
		ft_lstpushback(&env,
			ft_lstnew(fetch_db(&env_db, environ[i]), sizeof(t_db)));
		i++;
	}
	define_env_list(shell, env);
	if (env == NULL)
		return (FAILURE);
	return (SUCCESS);
}
